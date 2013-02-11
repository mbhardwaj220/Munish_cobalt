/*
 * Copyright 2012 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "media/filters/shell_avc_parser.h"

#include "base/stringprintf.h"
#include "lb_platform.h"
#include "media/base/shell_buffer_factory.h"
#include "media/filters/shell_rbsp_stream.h"
#include "media/mp4/aac.h"

namespace media {

// what's the smallest meaningful AVC config we can parse?
static const int kAVCConfigMinSize = 8;

// sampling frequency index according to subclause 1.6.3.4 in ISO14496-3.
static const int kAACSamplingFrequencyIndex[] = {
  96000,
  88200,
  64000,
  48000,
  44100,
  32000,
  24000,
  22050,
  16000,
  12000,
  11025,
  8000,
  7350,
  -1,
  -1,
  -1
};

// AnnexB start code is 4 bytes 0x00000001 big-endian
static const int kAnnexBStartCodeSize = 4;
static const uint32 kAnnexBStartCode = 0x00000001;

ShellAVCParser::ShellAVCParser(scoped_refptr<ShellDataSourceReader> reader)
    : ShellParser(reader)
    , nal_header_size_(0)
    , video_prepend_size_(0) {
}

ShellAVCParser::~ShellAVCParser() {
}

bool ShellAVCParser::Prepend(scoped_refptr<ShellAU> au,
                             scoped_refptr<ShellBuffer> buffer) {
  // sanity-check inputs
  if (!au || !buffer) {
    NOTREACHED() << "bad input to Prepend()";
    return false;
  }
  uint8* prepend_buffer = buffer->GetWritableData();
  if (!prepend_buffer || buffer->GetDataSize() < au->GetPrependSize()) {
    NOTREACHED() << "empty/undersized buffer to Prepend()";
    return false;
  }
  if (au->GetType() == DemuxerStream::VIDEO) {
    if (au->IsKeyframe()) {
      memcpy(prepend_buffer, video_prepend_, video_prepend_size_);
    } else {
      LB::Platform::store_uint32_big_endian(kAnnexBStartCode, prepend_buffer);
    }
  } else if (au->GetType() == DemuxerStream::AUDIO) {
    // audio, need to copy ADTS header and then add buffer size
    uint32 buffer_size = au->GetSize() + kADTSPrependSize;
    // we can't express an AU size larger than 13 bits, something's bad here.
    if (buffer_size & 0xffffe000) {
      return false;
    }
    memcpy(prepend_buffer, audio_prepend_, kADTSPrependSize);
    // OR size into buffer, byte 3 gets 2 MSb of 13-bit size
    prepend_buffer[3] |= (uint8)((buffer_size & 0x00001800) >> 11);
    // byte 4 gets bits 10-3 of size
    prepend_buffer[4] = (uint8)((buffer_size & 0x000007f8) >> 3);
    // byte 5 gets bits 2-0 of size
    prepend_buffer[5] |= (uint8)((buffer_size & 0x00000007) << 5);
  } else {
    NOTREACHED() << "unsupported demuxer stream type.";
    return false;
  }

  return true;
}

bool ShellAVCParser::DownloadAndParseAVCConfigRecord(uint64 offset,
                                                     uint32 size) {
  scoped_refptr<ShellScopedArray> record_buffer =
      ShellBufferFactory::Instance()->AllocateArray(size);
  // It's possible that the size of this record buffer may exceed the
  // memory available to the media stack, in which case we skip it.
  if (!record_buffer || !record_buffer->Get()) {
    DLOG(WARNING) << base::StringPrintf(
        "insufficient memory to download AVCConfigRecord of %d bytes",
        size);
    return false;
  }
  int bytes_read = reader_->BlockingRead(offset, size, record_buffer->Get());
  if (bytes_read < size) {
    return false;
  }
  // ok, successfully downloaded the record, parse it
  return ParseAVCConfigRecord(record_buffer->Get(), size);
}

bool ShellAVCParser::ParseAVCConfigRecord(uint8* buffer, uint32 size) {
  if (size < kAVCConfigMinSize) {
    DLOG(WARNING) << base::StringPrintf(
        "FLV AVCVIDEODATA configuration packet bad size: %d",
        size);
    return false;
  }

  // get the NALU header size
  nal_header_size_ = (buffer[4] & 0x03) + 1;
  // validate size, needs to be 1, 2 or 4 bytes only
  if (nal_header_size_ != 4 &&
      nal_header_size_ != 2 &&
      nal_header_size_ != 1) {
    return false;
  }
  // AVCConfigRecords contain a variable number of SPS NALU
  // (Sequence Parameter Set) (Network Abstraction Layer Units)
  // from which we can extract width, height, and cropping info.
  // That means we need at least 1 SPS NALU in this stream for extraction.
  uint8 number_of_sps_nalus = buffer[5] & 0x1f;
  if (number_of_sps_nalus == 0) {
    DLOG(WARNING) << "got AVCConfigRecord without any SPS NALUs!";
    return false;
  }
  // iterate through SPS NALUs finding one of valid size for our purposes
  // (this should usually be the first one), but also advancing through
  // the ConfigRecord until we encounter the PPS sets
  bool have_valid_sps = false;
  int record_offset = 6;
  size_t usable_sps_size = 0;
  int usable_sps_offset = 0;
  for (uint8 i = 0; i < number_of_sps_nalus; i++) {
    // make sure we haven't run out of record for the 2-byte size record
    if (record_offset + 2 > size) {
      DLOG(WARNING) << "ran out of AVCConfig record while parsing SPS size.";
      return false;
    }
    // extract 2-byte size of this SPS
    size_t sps_size = LB::Platform::load_uint16_big_endian(
        buffer + record_offset);
    // advance past the 2-byte size record
    record_offset += 2;
    // see if we jumped over record size
    if (record_offset + sps_size > size) {
      DLOG(WARNING) << "ran out of AVCConfig record while parsing SPS blocks.";
      return false;
    }
    if (!have_valid_sps) {
      have_valid_sps = true;
      // save size and offset for later copying and parsing
      usable_sps_size = sps_size;
      usable_sps_offset = record_offset;
      // continue to iterate through sps records to get to pps which follow
    }
    record_offset += sps_size;
  }
  if (!have_valid_sps) {
    DLOG(WARNING) <<
        "unable to parse a suitable SPS. Perhaps increase max size?";
    return false;
  }
  // we don't strictly require a PPS, so we're even willing to accept that
  // this could be the end of the bytestream, but if not the next byte should
  // define the number of PPS objects in the record. Not sure if
  // specific decoders could decode something without a PPS prepend but this
  // doesn't break demuxing so we'll let them complain if that isn't going
  // to work for them :)
  size_t usable_pps_size = 0;
  size_t usable_pps_offset = 0;
  bool have_valid_pps = false;
  if (record_offset + 1 < size) {
    uint8 number_of_pps_nalus = buffer[record_offset];
    record_offset++;
    for (uint8 i = 0; i < number_of_pps_nalus; i++) {
      // make sure we don't run out of room for 2-byte size record
      if (record_offset + 2 >= size) {
        DLOG(WARNING) << "ran out of AVCConfig record while parsing PPS size.";
        return false;
      }
      // extract 2-byte size of this PPS
      size_t pps_size = LB::Platform::load_uint16_big_endian(
          buffer + record_offset);
      record_offset += 2;
      // see if there's actually room for this record in the buffer
      if (record_offset + pps_size > size) {
        DLOG(WARNING) <<
            "ran out of AVCConfig record while scanning PPS blocks.";
        return false;
      }
      if (!have_valid_pps) {
        have_valid_pps = true;
        usable_pps_size = pps_size;
        usable_pps_offset = record_offset;
        break;
      }
    }
  }
  // now we parse the valid SPS we extracted from byte stream earlier.
  // first convert SPS NALU to RBSP stream
  ShellRBSPStream s(buffer + usable_sps_offset, usable_sps_size);
  uint8 profile_idc = 0;
  if (!s.ReadByte(profile_idc)) {
    DLOG(WARNING) << "failure reading profile_idc from sps RBSP";
    return false;
  }
  // skip 3 constraint flags, 5 reserved bits, and level_idc (16 bits)
  s.SkipBytes(2);
  // ReadUEV/ReadSEV require a value to be passed by reference but
  // there are many times in which we ignore this value.
  uint32 disposable_uev = 0;
  int32 disposable_sev = 0;
  // seq_parameter_set_id
  s.ReadUEV(disposable_uev);
  // skip profile-specific encoding information if there
  if (profile_idc == 100 || profile_idc == 103 ||
      profile_idc == 110 || profile_idc == 122 ||
      profile_idc == 244 || profile_idc == 44 ||
      profile_idc == 83 || profile_idc == 86 ||
      profile_idc == 118) {
    uint32 chroma_format_idc = 0;
    if (!s.ReadUEV(chroma_format_idc)) {
      DLOG(WARNING) << "failure reading chroma_format_idc from sps RBSP";
      return false;
    }
    if (chroma_format_idc == 3) {
      // separate_color_plane_flag
      s.SkipBits(1);
    }
    // bit_depth_luma_minus8
    s.ReadUEV(disposable_uev);
    // bit_depth_chroma_minus8
    s.ReadUEV(disposable_uev);
    // qpprime_y_zero_transform_bypass_flag
    s.SkipBits(1);
    // seq_scaling_matrix_present_flag
    uint8 seq_scaling_matrix_present_flag = 0;
    if (!s.ReadBit(seq_scaling_matrix_present_flag)) {
      DLOG(WARNING) <<
          "failure reading seq_scaling_matrix_present_flag from sps RBSP";
      return false;
    }
    if (seq_scaling_matrix_present_flag) {
      // seq_scaling_list_present_flag[]
      s.SkipBits(chroma_format_idc != 3 ? 8 : 12);
    }
  }
  // log2_max_frame_num_minus4
  s.ReadUEV(disposable_uev);
  // pic_order_cnt_type
  uint32 pic_order_cnt_type = 0;
  if (!s.ReadUEV(pic_order_cnt_type)) {
    DLOG(WARNING) << "failure reading pic_order_cnt_type from sps RBSP";
    return false;
  }
  if (pic_order_cnt_type == 0) {
    // log2_max_pic_order_cnt_lsb_minus4
    s.ReadUEV(disposable_uev);
  } else if (pic_order_cnt_type == 1) {
    // delta_pic_order_always_zero_flag
    s.SkipBits(1);
    // offset_for_non_ref_pic
    s.ReadSEV(disposable_sev);
    // offset_for_top_to_bottom_field
    s.ReadSEV(disposable_sev);
    // num_ref_frames_in_pic_order_cnt_cycle
    uint32 num_ref_frames_in_pic_order_cnt_cycle = 0;
    if (!s.ReadUEV(num_ref_frames_in_pic_order_cnt_cycle)) {
      DLOG(WARNING) <<
          "failure reading num_ref_frames_in_pic_order_cnt_cycle from sps";
      return false;
    }
    for (uint32 i = 0;
         i < num_ref_frames_in_pic_order_cnt_cycle; ++i) {
      s.ReadSEV(disposable_sev);
    }
  }
  // number of reference frames used to decode
  num_ref_frames_ = 0;
  if (!s.ReadUEV(num_ref_frames_)) {
    DLOG(WARNING) << "failure reading number of ref frames from sps RBSP";
    return false;
  }
  // gaps_in_frame_num_value_allowed_flag
  s.SkipBits(1);
  // width is calculated from pic_width_in_mbs_minus1
  uint32 pic_width_in_mbs_minus1 = 0;
  if (!s.ReadUEV(pic_width_in_mbs_minus1)) {
    DLOG(WARNING) << "failure reading image width from sps RBSP";
    return false;
  }
  // 16 pxs per macroblock
  uint32 width = (pic_width_in_mbs_minus1 + 1) * 16;
  // pic_height_in_map_units_minus1
  uint32 pic_height_in_map_units_minus1 = 0;
  if (!s.ReadUEV(pic_height_in_map_units_minus1)) {
    DLOG(WARNING) <<
        "failure reading pic_height_in_map_uints_minus1 from sps RBSP";
    return false;
  }
  uint8 frame_mbs_only_flag = 0;
  if (!s.ReadBit(frame_mbs_only_flag)) {
    DLOG(WARNING) << "failure reading frame_mbs_only_flag from sps RBSP";
    return false;
  }
  uint32 height = (2 - (uint32)frame_mbs_only_flag)
                  * (pic_height_in_map_units_minus1 + 1)
                  * 16;
  if (!frame_mbs_only_flag) {
    s.SkipBits(1);
  }
  // direct_8x8_inference_flag
  s.SkipBits(1);
  // frame cropping flag
  uint8 frame_cropping_flag = 0;
  if (!s.ReadBit(frame_cropping_flag)) {
    DLOG(WARNING) << "failure reading frame_cropping_flag from sps RBSP";
    return false;
  }
  // distance in pixels from the associated edge of the media:
  //
  // <---coded_size---width--------------------->
  //
  // +------------------------------------------+   ^
  // |                 ^                        |   |
  // |                 |                        |   |
  // |              crop_top                    |   |
  // |                 |                        |   |
  // |                 v                        | height
  // |               +---------+                |   |
  // |<--crop_left-->| visible |                |   |
  // |               |   rect  |<--crop_right-->|   |
  // |               +---------+                |   |
  // |                  ^                       |   |
  // |                  |                       |   |
  // |              crop_bottom                 |   |
  // |                  |                       |   |
  // |                  v                       |   |
  // +------------------------------------------+   v
  //
  uint32 crop_left = 0;
  uint32 crop_right = 0;
  uint32 crop_top = 0;
  uint32 crop_bottom = 0;
  // cropping values are stored divided by two
  if (frame_cropping_flag) {
    if (!s.ReadUEV(crop_left)) {
      DLOG(WARNING) << "failure reading crop_left from sps RBSP";
      return false;
    }
    if (!s.ReadUEV(crop_right)) {
      DLOG(WARNING) << "failure reading crop_right from sps RBSP";
      return false;
    }
    if (!s.ReadUEV(crop_top)) {
      DLOG(WARNING) << "failure reading crop_top from sps RBSP";
      return false;
    }
    if (!s.ReadUEV(crop_bottom)) {
      DLOG(WARNING) << "failure reading crop_bottom from sps RBSP";
      return false;
    }
    crop_left *= 2;
    crop_right *= 2;
    crop_top *= 2;
    crop_bottom *= 2;
  }
  // remainder of SPS are values we can safely ignore

  // populate extra data structure for copying into config
  AVCExtraData extra_data;
  extra_data.num_ref_frames = num_ref_frames_;

  int visible_width = width - (crop_left + crop_right);
  int visible_height = height - (crop_top + crop_bottom);
  // we can now initialize our video decoder config
  video_config_.Initialize(
      kCodecH264,
      H264PROFILE_MAIN,             // profile is ignored currently
      VideoFrame::NATIVE_TEXTURE,   // we always decode directly to texture
      gfx::Size(width, height),
      gfx::Rect(crop_left, crop_top, visible_width, visible_height),
      gfx::Size(visible_width, visible_height),
      // attach our extra data structure
      (const uint8*)&extra_data, sizeof(AVCExtraData),
      // is not currently encrypted
      false,
      // ignore stats for now
      false);

  return BuildAnnexBPrepend(buffer + usable_sps_offset,
                            usable_sps_size,
                            buffer + usable_pps_offset,
                            usable_pps_size);
}

bool ShellAVCParser::BuildAnnexBPrepend(uint8* sps,
                                        uint32 sps_size,
                                        uint8* pps,
                                        uint32 pps_size) {
  // We will need to attach the sps and pps (if provided) to each keyframe
  // video packet, with the AnnexB start code in front of each, followed by an
  // additional start code for the data.  Start with sps size and start code
  // plus data start code.
  video_prepend_size_ = sps_size + (kAnnexBStartCodeSize * 2);
  if (pps_size > 0) {
    // Add pps and pps start code size if needed.
    video_prepend_size_ += pps_size + kAnnexBStartCodeSize;
  }
  // this should be a very rare case for typical videos
  if (video_prepend_size_ > kAnnexBPrependMaxSize) {
    NOTREACHED() << base::StringPrintf("Bad AnnexB prepend size: %d",
                                       video_prepend_size_);
    return false;
  }
  // start code for sps comes first
  LB::Platform::store_uint32_big_endian(kAnnexBStartCode, video_prepend_);
  // followed by sps body
  memcpy(video_prepend_ + kAnnexBStartCodeSize, sps, sps_size);
  int prepend_offset = kAnnexBStartCodeSize + sps_size;
  if (pps_size > 0) {
    // pps start code comes next
    LB::Platform::store_uint32_big_endian(kAnnexBStartCode,
                                          video_prepend_ + prepend_offset);
    prepend_offset += kAnnexBStartCodeSize;
    // followed by pps
    memcpy(video_prepend_ + prepend_offset, pps, pps_size);
    prepend_offset += pps_size;
  }

  // finally followed by data start code
  LB::Platform::store_uint32_big_endian(kAnnexBStartCode,
                                        video_prepend_ + prepend_offset);
  // make sure we haven't wandered off into memory somewhere
  DCHECK_EQ(prepend_offset + kAnnexBStartCodeSize, video_prepend_size_);
  return true;
}

void ShellAVCParser::ParseAudioSpecificConfig(uint8 b0, uint8 b1) {
  // see http://wiki.multimedia.cx/index.php?title=Understanding_AAC for
  // best description of bit packing within these two bytes, basically
  // aaaaabbb bccccdef
  // aaaaa: 5 bits of aac object type
  // bbbb: 4 bits of frequency table index
  // cccc: 4 bits of channel config index
  uint8 aac_object_type = (b0 >> 3) & 0x1f;
  uint8 sample_freq_index = ((b0 & 0x07) << 1) |
                            ((b1 & 0x80) >> 7) & 0x0f;
  int frequency = kAACSamplingFrequencyIndex[sample_freq_index];
  uint8 channel_config = ((b1 & 0x78) >> 3) & 0x0f;
  ChannelLayout channel_layout = mp4::AAC::GetChannelLayout(channel_config);
  audio_config_.Initialize(kCodecAAC,
                           16,   // AAC is always 16 bit
                           channel_layout,
                           frequency,
                           NULL,
                           0,
                           false,
                           false);

  // Now we have sufficient data to build the ADTS header, do so now. This
  // explanation of the ADTS header is adopted from the text at:
  // http://wiki.multimedia.cx/index.php?title=ADTS.
  //
  // ADTS is 7 bytes as we always omit the 2-byte optional data CRC. Each byte
  // is bitpacked values, layout is as follows:
  //
  // aaaaaaaa aaaabccd eeffffgh hhijklmm mmmmmmmm mmmooooo oooooopp
  //
  // key | bits | description
  // a   | 12   | syncword 0xfff, all bits are 1
  // b   | 1    | mpeg version, set to 0 for mp4
  // c   | 2    | layer, always 0
  // d   | 1    | protection absent, always 1 for no CRC
  // e   | 2    | mp4 aac_object_type minus 1
  // f   | 4    | mp4 sampling frequency index
  // g   | 1    | private stream, ignored, set to 0
  // h   | 3    | mp4 channel config
  // i   | 1    | originality, ignored, set to 0
  // j   | 1    | home, ignored, set to 0
  // k   | 1    | copyrighted, ignored, set to 0
  // l   | 1    | copyright start, ignored, set to 0
  // m   | 13   | frame length in bytes including header, set on every buffer
  // n   | 0    | there is no letter n
  // o   | 11   | buffer fullness, leave at all 1s
  // p   | 2    | number of NALUs in this packet minus 1, for us always 1
  //
  // bytes 0 and 1 aaaaaaaa aaaabccd are constant, set them now
  LB::Platform::store_uint16_big_endian(0xfff1, audio_prepend_);
  // byte 2 is eeffffgh
  audio_prepend_[2] = (aac_object_type - 1) << 6       |
                      (sample_freq_index & 0x0f) << 2  |
                      (channel_config & 0x04) >> 2;
  // byte 3 is hhijklmm, we leave m at 0 for now
  audio_prepend_[3] = (channel_config & 0x03) << 6;
  // byte 4 is mmmmmmmm, leave at 0 for now
  audio_prepend_[4] = 0;
  // byte 5 is mmmooooo, fullness needs to be all 1s, put them in place
  audio_prepend_[5] = 0x1f;
  // byte 6 is oooooopp, fullnes and constant NALU count - 1 of 0
  audio_prepend_[6] = 0xfc;
}

size_t ShellAVCParser::CalculatePrependSize(DemuxerStream::Type type,
                                            bool is_keyframe) {
  size_t prepend_size = 0;
  if (type == DemuxerStream::VIDEO) {
    if (is_keyframe) {
      prepend_size = video_prepend_size_;
    } else {
      prepend_size = kAnnexBStartCodeSize;
    }
  } else if (type == DemuxerStream::AUDIO) {
    prepend_size = kADTSPrependSize;  // fixed-size audio prepend
  } else {
    NOTREACHED() << "unsupported stream type";
  }
  return prepend_size;
}

}  // namespace media
