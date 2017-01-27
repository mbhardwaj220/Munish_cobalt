// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "media2/base/audio_buffer_queue.h"

#include <stdint.h>

#include <limits>
#include <memory>

#include "base/logging.h"
#include "base/time.h"
#include "media2/base/audio_buffer.h"
#include "media2/base/audio_bus.h"
#include "media2/base/test_helpers.h"
#include "media2/base/timestamp_constants.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace media {

const int kSampleRate = 44100;

static void VerifyBus(AudioBus* bus,
                      int offset,
                      int frames,
                      int buffer_size,
                      float start,
                      float increment) {
  for (int ch = 0; ch < bus->channels(); ++ch) {
    const float v = start + ch * buffer_size * increment;
    for (int i = offset; i < offset + frames; ++i) {
      ASSERT_FLOAT_EQ(v + (i - offset) * increment, bus->channel(ch)[i])
          << "i=" << i << ", ch=" << ch;
    }
  }
}

template <typename T>
static scoped_refptr<AudioBuffer> MakeTestBuffer(SampleFormat format,
                                                 ChannelLayout channel_layout,
                                                 T start,
                                                 T step,
                                                 int frames) {
  return MakeAudioBuffer<T>(format, channel_layout,
                            ChannelLayoutToChannelCount(channel_layout),
                            kSampleRate, start, step, frames, kNoTimestamp);
}

TEST(AudioBufferQueueTest, AppendAndClear) {
  const ChannelLayout channel_layout = CHANNEL_LAYOUT_MONO;
  AudioBufferQueue buffer;
  EXPECT_EQ(0, buffer.frames());
  buffer.Append(
      MakeTestBuffer<uint8_t>(kSampleFormatU8, channel_layout, 10, 1, 8));
  EXPECT_EQ(8, buffer.frames());
  buffer.Clear();
  EXPECT_EQ(0, buffer.frames());
  buffer.Append(
      MakeTestBuffer<uint8_t>(kSampleFormatU8, channel_layout, 20, 1, 8));
  EXPECT_EQ(8, buffer.frames());
}

TEST(AudioBufferQueueTest, MultipleAppend) {
  const ChannelLayout channel_layout = CHANNEL_LAYOUT_MONO;
  AudioBufferQueue buffer;
  buffer.Append(
      MakeTestBuffer<uint8_t>(kSampleFormatU8, channel_layout, 10, 1, 8));
  EXPECT_EQ(8, buffer.frames());
  buffer.Append(
      MakeTestBuffer<uint8_t>(kSampleFormatU8, channel_layout, 10, 1, 8));
  EXPECT_EQ(16, buffer.frames());
  buffer.Append(
      MakeTestBuffer<uint8_t>(kSampleFormatU8, channel_layout, 10, 1, 8));
  EXPECT_EQ(24, buffer.frames());
  buffer.Append(
      MakeTestBuffer<uint8_t>(kSampleFormatU8, channel_layout, 10, 1, 8));
  EXPECT_EQ(32, buffer.frames());
  buffer.Append(
      MakeTestBuffer<uint8_t>(kSampleFormatU8, channel_layout, 10, 1, 8));
  EXPECT_EQ(40, buffer.frames());
}

TEST(AudioBufferQueueTest, IteratorCheck) {
  const ChannelLayout channel_layout = CHANNEL_LAYOUT_MONO;
  const int channels = ChannelLayoutToChannelCount(channel_layout);
  AudioBufferQueue buffer;
  std::unique_ptr<AudioBus> bus = AudioBus::Create(channels, 100);

  // Append 40 frames in 5 buffers. Intersperse ReadFrames() to make the
  // iterator is pointing to the correct position.
  buffer.Append(MakeTestBuffer<float>(
      kSampleFormatF32, channel_layout, 10.0f, 1.0f, 8));
  EXPECT_EQ(8, buffer.frames());

  EXPECT_EQ(4, buffer.ReadFrames(4, 0, bus.get()));
  EXPECT_EQ(4, buffer.frames());
  VerifyBus(bus.get(), 0, 4, bus->frames(), 10, 1);

  buffer.Append(MakeTestBuffer<float>(
      kSampleFormatF32, channel_layout, 20.0f, 1.0f, 8));
  EXPECT_EQ(12, buffer.frames());
  buffer.Append(MakeTestBuffer<float>(
      kSampleFormatF32, channel_layout, 30.0f, 1.0f, 8));
  EXPECT_EQ(20, buffer.frames());

  buffer.SeekFrames(16);
  EXPECT_EQ(4, buffer.ReadFrames(4, 0, bus.get()));
  EXPECT_EQ(0, buffer.frames());
  VerifyBus(bus.get(), 0, 4, bus->frames(), 34, 1);

  buffer.Append(MakeTestBuffer<float>(
      kSampleFormatF32, channel_layout, 40.0f, 1.0f, 8));
  EXPECT_EQ(8, buffer.frames());
  buffer.Append(MakeTestBuffer<float>(
      kSampleFormatF32, channel_layout, 50.0f, 1.0f, 8));
  EXPECT_EQ(16, buffer.frames());

  EXPECT_EQ(4, buffer.ReadFrames(4, 0, bus.get()));
  VerifyBus(bus.get(), 0, 4, bus->frames(), 40, 1);

  // Read off the end of the buffer.
  EXPECT_EQ(12, buffer.frames());
  buffer.SeekFrames(8);
  EXPECT_EQ(4, buffer.ReadFrames(100, 0, bus.get()));
  VerifyBus(bus.get(), 0, 4, bus->frames(), 54, 1);
}

TEST(AudioBufferQueueTest, Seek) {
  const ChannelLayout channel_layout = CHANNEL_LAYOUT_STEREO;
  AudioBufferQueue buffer;

  // Add 6 frames of data.
  buffer.Append(MakeTestBuffer<float>(
      kSampleFormatF32, channel_layout, 1.0f, 1.0f, 6));
  EXPECT_EQ(6, buffer.frames());

  // Seek past 2 frames.
  buffer.SeekFrames(2);
  EXPECT_EQ(4, buffer.frames());

  // Seek to end of data.
  buffer.SeekFrames(4);
  EXPECT_EQ(0, buffer.frames());

  // At end, seek now fails unless 0 specified.
  buffer.SeekFrames(0);
}

TEST(AudioBufferQueueTest, ReadF32) {
  const ChannelLayout channel_layout = CHANNEL_LAYOUT_STEREO;
  const int channels = ChannelLayoutToChannelCount(channel_layout);
  AudioBufferQueue buffer;

  // Add 76 frames of data.
  buffer.Append(
      MakeTestBuffer<float>(kSampleFormatF32, channel_layout, 1.0f, 1.0f, 6));
  buffer.Append(
      MakeTestBuffer<float>(kSampleFormatF32, channel_layout, 13.0f, 1.0f, 10));
  buffer.Append(
      MakeTestBuffer<float>(kSampleFormatF32, channel_layout, 33.0f, 1.0f, 60));
  EXPECT_EQ(76, buffer.frames());

  // Read 3 frames from the buffer.
  std::unique_ptr<AudioBus> bus = AudioBus::Create(channels, 100);
  EXPECT_EQ(3, buffer.ReadFrames(3, 0, bus.get()));
  EXPECT_EQ(73, buffer.frames());
  VerifyBus(bus.get(), 0, 3, 6, 1, 1);

  // Now read 5 frames, which will span buffers. Append the data into AudioBus.
  EXPECT_EQ(5, buffer.ReadFrames(5, 3, bus.get()));
  EXPECT_EQ(68, buffer.frames());
  VerifyBus(bus.get(), 0, 6, 6, 1, 1);
  VerifyBus(bus.get(), 6, 2, 10, 13, 1);

  // Now skip into the third buffer.
  buffer.SeekFrames(20);
  EXPECT_EQ(48, buffer.frames());

  // Now read 2 frames, which are in the third buffer.
  EXPECT_EQ(2, buffer.ReadFrames(2, 0, bus.get()));
  VerifyBus(bus.get(), 0, 2, 60, 45, 1);
}

TEST(AudioBufferQueueTest, ReadU8) {
  const ChannelLayout channel_layout = CHANNEL_LAYOUT_4_0;
  const int channels = ChannelLayoutToChannelCount(channel_layout);
  const int frames = 4;
  AudioBufferQueue buffer;

  // Add 4 frames of data.
  buffer.Append(
      MakeTestBuffer<uint8_t>(kSampleFormatU8, channel_layout, 128, 1, frames));

  // Read all 4 frames from the buffer.
  std::unique_ptr<AudioBus> bus = AudioBus::Create(channels, frames);
  EXPECT_EQ(frames, buffer.ReadFrames(frames, 0, bus.get()));
  EXPECT_EQ(0, buffer.frames());
  VerifyBus(bus.get(), 0, frames, bus->frames(), 0, 1.0f / 127.0f);
}

TEST(AudioBufferQueueTest, ReadS16) {
  const ChannelLayout channel_layout = CHANNEL_LAYOUT_STEREO;
  const int channels = ChannelLayoutToChannelCount(channel_layout);
  AudioBufferQueue buffer;

  // Add 24 frames of data.
  buffer.Append(
      MakeTestBuffer<int16_t>(kSampleFormatS16, channel_layout, 1, 1, 4));
  buffer.Append(
      MakeTestBuffer<int16_t>(kSampleFormatS16, channel_layout, 9, 1, 20));
  EXPECT_EQ(24, buffer.frames());

  // Read 6 frames from the buffer.
  const int frames = 6;
  std::unique_ptr<AudioBus> bus = AudioBus::Create(channels, buffer.frames());
  EXPECT_EQ(frames, buffer.ReadFrames(frames, 0, bus.get()));
  EXPECT_EQ(18, buffer.frames());
  VerifyBus(bus.get(), 0, 4, 4, 1.0f / std::numeric_limits<int16_t>::max(),
            1.0f / std::numeric_limits<int16_t>::max());
  VerifyBus(bus.get(), 4, 2, 20, 9.0f / std::numeric_limits<int16_t>::max(),
            1.0f / std::numeric_limits<int16_t>::max());
}

TEST(AudioBufferQueueTest, ReadS32) {
  const ChannelLayout channel_layout = CHANNEL_LAYOUT_STEREO;
  const int channels = ChannelLayoutToChannelCount(channel_layout);
  AudioBufferQueue buffer;

  // Add 24 frames of data.
  buffer.Append(
      MakeTestBuffer<int32_t>(kSampleFormatS32, channel_layout, 1, 1, 4));
  buffer.Append(
      MakeTestBuffer<int32_t>(kSampleFormatS32, channel_layout, 9, 1, 20));
  EXPECT_EQ(24, buffer.frames());

  // Read 6 frames from the buffer.
  std::unique_ptr<AudioBus> bus = AudioBus::Create(channels, 100);
  EXPECT_EQ(6, buffer.ReadFrames(6, 0, bus.get()));
  EXPECT_EQ(18, buffer.frames());
  VerifyBus(bus.get(), 0, 4, 4, 1.0f / std::numeric_limits<int32_t>::max(),
            1.0f / std::numeric_limits<int32_t>::max());
  VerifyBus(bus.get(), 4, 2, 20, 9.0f / std::numeric_limits<int32_t>::max(),
            1.0f / std::numeric_limits<int32_t>::max());

  // Read the next 2 frames.
  EXPECT_EQ(2, buffer.ReadFrames(2, 0, bus.get()));
  EXPECT_EQ(16, buffer.frames());
  VerifyBus(bus.get(), 0, 2, 20, 11.0f / std::numeric_limits<int32_t>::max(),
            1.0f / std::numeric_limits<int32_t>::max());
}

TEST(AudioBufferQueueTest, ReadF32Planar) {
  const ChannelLayout channel_layout = CHANNEL_LAYOUT_STEREO;
  const int channels = ChannelLayoutToChannelCount(channel_layout);
  AudioBufferQueue buffer;

  // Add 14 frames of data.
  buffer.Append(MakeTestBuffer<float>(
      kSampleFormatPlanarF32, channel_layout, 1.0f, 1.0f, 4));
  buffer.Append(MakeTestBuffer<float>(
      kSampleFormatPlanarF32, channel_layout, 50.0f, 1.0f, 10));
  EXPECT_EQ(14, buffer.frames());

  // Read 6 frames from the buffer.
  std::unique_ptr<AudioBus> bus = AudioBus::Create(channels, 100);
  EXPECT_EQ(6, buffer.ReadFrames(6, 0, bus.get()));
  EXPECT_EQ(8, buffer.frames());
  VerifyBus(bus.get(), 0, 4, 4, 1, 1);
  VerifyBus(bus.get(), 4, 2, 10, 50, 1);
}

TEST(AudioBufferQueueTest, ReadS16Planar) {
  const ChannelLayout channel_layout = CHANNEL_LAYOUT_STEREO;
  const int channels = ChannelLayoutToChannelCount(channel_layout);
  AudioBufferQueue buffer;

  // Add 24 frames of data.
  buffer.Append(
      MakeTestBuffer<int16_t>(kSampleFormatPlanarS16, channel_layout, 1, 1, 4));
  buffer.Append(MakeTestBuffer<int16_t>(kSampleFormatPlanarS16, channel_layout,
                                        5, 1, 20));
  EXPECT_EQ(24, buffer.frames());

  // Read 6 frames from the buffer.
  std::unique_ptr<AudioBus> bus = AudioBus::Create(channels, 100);
  EXPECT_EQ(6, buffer.ReadFrames(6, 0, bus.get()));
  EXPECT_EQ(18, buffer.frames());
  VerifyBus(bus.get(), 0, 4, 4, 1.0f / std::numeric_limits<int16_t>::max(),
            1.0f / std::numeric_limits<int16_t>::max());
  VerifyBus(bus.get(), 4, 2, 20, 5.0f / std::numeric_limits<int16_t>::max(),
            1.0f / std::numeric_limits<int16_t>::max());
}

TEST(AudioBufferQueueTest, ReadManyChannels) {
  const ChannelLayout channel_layout = CHANNEL_LAYOUT_OCTAGONAL;
  const int channels = ChannelLayoutToChannelCount(channel_layout);
  AudioBufferQueue buffer;

  // Add 76 frames of data.
  buffer.Append(
      MakeTestBuffer<float>(kSampleFormatF32, channel_layout, 0.0f, 1.0f, 6));
  buffer.Append(MakeTestBuffer<float>(
      kSampleFormatF32, channel_layout, 6.0f * channels, 1.0f, 10));
  buffer.Append(MakeTestBuffer<float>(
      kSampleFormatF32, channel_layout, 16.0f * channels, 1.0f, 60));
  EXPECT_EQ(76, buffer.frames());

  // Read 3 frames from the buffer.
  std::unique_ptr<AudioBus> bus = AudioBus::Create(channels, 100);
  EXPECT_EQ(30, buffer.ReadFrames(30, 0, bus.get()));
  EXPECT_EQ(46, buffer.frames());
  VerifyBus(bus.get(), 0, 6, 6, 0, 1);
  VerifyBus(bus.get(), 6, 10, 10, 6 * channels, 1);
  VerifyBus(bus.get(), 16, 14, 60, 16 * channels, 1);
}

TEST(AudioBufferQueueTest, Peek) {
  const ChannelLayout channel_layout = CHANNEL_LAYOUT_4_0;
  const int channels = ChannelLayoutToChannelCount(channel_layout);
  AudioBufferQueue buffer;

  // Add 60 frames of data.
  const int frames = 60;
  buffer.Append(MakeTestBuffer<float>(
      kSampleFormatF32, channel_layout, 0.0f, 1.0f, frames));
  EXPECT_EQ(frames, buffer.frames());

  // Peek at the first 30 frames.
  std::unique_ptr<AudioBus> bus1 = AudioBus::Create(channels, frames);
  EXPECT_EQ(frames, buffer.frames());
  EXPECT_EQ(frames, buffer.PeekFrames(60, 0, 0, bus1.get()));
  EXPECT_EQ(30, buffer.PeekFrames(30, 0, 0, bus1.get()));
  EXPECT_EQ(frames, buffer.frames());
  VerifyBus(bus1.get(), 0, 30, bus1->frames(), 0, 1);

  // Now read the next 30 frames (which should be the same as those peeked at).
  std::unique_ptr<AudioBus> bus2 = AudioBus::Create(channels, frames);
  EXPECT_EQ(30, buffer.ReadFrames(30, 0, bus2.get()));
  VerifyBus(bus2.get(), 0, 30, bus2->frames(), 0, 1);

  // Peek 10 frames forward
  bus1->Zero();
  EXPECT_EQ(5, buffer.PeekFrames(5, 10, 0, bus1.get()));
  VerifyBus(bus1.get(), 0, 5, bus1->frames(), 40, 1);

  // Peek to the end of the buffer.
  EXPECT_EQ(30, buffer.frames());
  EXPECT_EQ(30, buffer.PeekFrames(60, 0, 0, bus1.get()));
  EXPECT_EQ(30, buffer.PeekFrames(30, 0, 0, bus1.get()));
}

}  // namespace media
