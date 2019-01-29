// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COBALT_MEDIA_FORMATS_MP4_FOURCCS_H_
#define COBALT_MEDIA_FORMATS_MP4_FOURCCS_H_

#include <string>

namespace cobalt {
namespace media {
namespace mp4 {

enum FourCC {
  FOURCC_NULL = 0,
  FOURCC_AC3 = 0x61632d33,   // "ac-3"
  FOURCC_EAC3 = 0x65632d33,  // "ec-3"
  FOURCC_AV01 = 0x61763031,  // "av01"
  FOURCC_AV1C = 0x61763143,  // "av1C"
  FOURCC_AVC1 = 0x61766331,
  FOURCC_AVC3 = 0x61766333,
  FOURCC_AVCC = 0x61766343,
  FOURCC_BLOC = 0x626C6F63,
  FOURCC_CENC = 0x63656e63,
  FOURCC_CO64 = 0x636f3634,
  FOURCC_CTTS = 0x63747473,
  FOURCC_DINF = 0x64696e66,
  FOURCC_EDTS = 0x65647473,
  FOURCC_EMSG = 0x656d7367,
  FOURCC_ELST = 0x656c7374,
  FOURCC_ENCA = 0x656e6361,
  FOURCC_ENCV = 0x656e6376,
  FOURCC_ESDS = 0x65736473,
  FOURCC_FREE = 0x66726565,
  FOURCC_FRMA = 0x66726d61,
  FOURCC_FTYP = 0x66747970,
  FOURCC_HDLR = 0x68646c72,
  FOURCC_HINT = 0x68696e74,
  FOURCC_HEV1 = 0x68657631,
  FOURCC_HVC1 = 0x68766331,
  FOURCC_HVCC = 0x68766343,
  FOURCC_IODS = 0x696f6473,
  FOURCC_MDAT = 0x6d646174,
  FOURCC_MDHD = 0x6d646864,
  FOURCC_MDIA = 0x6d646961,
  FOURCC_MECO = 0x6d65636f,
  FOURCC_MEHD = 0x6d656864,
  FOURCC_META = 0x6d657461,
  FOURCC_MFHD = 0x6d666864,
  FOURCC_MFRA = 0x6d667261,
  FOURCC_MINF = 0x6d696e66,
  FOURCC_MOOF = 0x6d6f6f66,
  FOURCC_MOOV = 0x6d6f6f76,
  FOURCC_MP4A = 0x6d703461,
  FOURCC_MP4V = 0x6d703476,
  FOURCC_MVEX = 0x6d766578,
  FOURCC_MVHD = 0x6d766864,
  FOURCC_PASP = 0x70617370,
  FOURCC_PDIN = 0x7064696e,
  FOURCC_PRFT = 0x70726674,
  FOURCC_PSSH = 0x70737368,
  FOURCC_SAIO = 0x7361696f,
  FOURCC_SAIZ = 0x7361697a,
  FOURCC_SBGP = 0x73626770,
  FOURCC_SBTL = 0x7362746c,
  FOURCC_SCHI = 0x73636869,
  FOURCC_SCHM = 0x7363686d,
  FOURCC_SDTP = 0x73647470,
  FOURCC_SEIG = 0x73656967,
  FOURCC_SENC = 0x73656e63,
  FOURCC_SGPD = 0x73677064,
  FOURCC_SIDX = 0x73696478,
  FOURCC_SINF = 0x73696e66,
  FOURCC_SKIP = 0x736b6970,
  FOURCC_SMHD = 0x736d6864,
  FOURCC_SOUN = 0x736f756e,
  FOURCC_SSIX = 0x73736978,
  FOURCC_STBL = 0x7374626c,
  FOURCC_STCO = 0x7374636f,
  FOURCC_STSC = 0x73747363,
  FOURCC_STSD = 0x73747364,
  FOURCC_STSS = 0x73747373,
  FOURCC_STSZ = 0x7374737a,
  FOURCC_STTS = 0x73747473,
  FOURCC_STYP = 0x73747970,
  FOURCC_SUBT = 0x73756274,
  FOURCC_TENC = 0x74656e63,
  FOURCC_TEXT = 0x74657874,
  FOURCC_TFDT = 0x74666474,
  FOURCC_TFHD = 0x74666864,
  FOURCC_TKHD = 0x746b6864,
  FOURCC_TRAF = 0x74726166,
  FOURCC_TRAK = 0x7472616b,
  FOURCC_TREX = 0x74726578,
  FOURCC_TRUN = 0x7472756e,
  FOURCC_UDTA = 0x75647461,
  FOURCC_UUID = 0x75756964,
  FOURCC_VIDE = 0x76696465,
  FOURCC_VMHD = 0x766d6864,
  FOURCC_VP09 = 0x76703039,
  FOURCC_VPCC = 0x76706343,
  FOURCC_WIDE = 0x77696465,
};

const inline std::string FourCCToString(FourCC fourcc) {
  char buf[5];
  buf[0] = (fourcc >> 24) & 0xff;
  buf[1] = (fourcc >> 16) & 0xff;
  buf[2] = (fourcc >> 8) & 0xff;
  buf[3] = (fourcc)&0xff;
  buf[4] = 0;

  // Return hex itself if characters can not be printed. Any character within
  // the "C" locale is considered printable.
  for (int i = 0; i < 4; ++i) {
    if (!(buf[i] > 0x1f && buf[i] < 0x7f)) {
      std::stringstream hex_string;
      hex_string << "0x" << std::hex << fourcc;
      return hex_string.str();
    }
  }

  return std::string(buf);
}

}  // namespace mp4
}  // namespace media
}  // namespace cobalt

#endif  // COBALT_MEDIA_FORMATS_MP4_FOURCCS_H_
