// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/logging.h"
#include "base/basictypes.h"
#include "base/scoped_ptr.h"
#include "base/time.h"
#include "media/audio/fake_audio_output_stream.h"
#include "media/audio/simple_sources.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace {

void GenerateRandomData(char* buffer, uint32 len) {
  static bool called = false;
  if (!called) {
    called = true;
    int seed = static_cast<int>(base::Time::Now().ToInternalValue());
    srand(seed);
    LOG(INFO) << "Random seed: " << seed;
  }

  for (uint32 i = 0; i < len; i++) {
    buffer[i] = static_cast<char>(rand());
  }
}

}  // namespace

// To test write size smaller than read size.
TEST(SimpleSourcesTest, PushSourceSmallerWrite) {
  const uint32 kDataSize = 40960;
  scoped_array<char> data(new char[kDataSize]);
  GenerateRandomData(data.get(), kDataSize);

  // Choose two prime numbers for read and write sizes.
  const uint32 kWriteSize = 283;
  const uint32 kReadSize = 293;
  scoped_array<char> read_data(new char[kReadSize]);

  // Create a PushSource.
  PushSource push_source;
  EXPECT_EQ(0u, push_source.UnProcessedBytes());

  // Write everything into this push source.
  for (uint32 i = 0; i < kDataSize; i += kWriteSize) {
    uint32 size = std::min(kDataSize - i, kWriteSize);
    EXPECT_TRUE(push_source.Write(data.get() + i, size));
  }
  EXPECT_EQ(kDataSize, push_source.UnProcessedBytes());

  // Read everything from the push source.
  for (uint32 i = 0; i < kDataSize; i += kReadSize) {
    uint32 size = std::min(kDataSize - i , kReadSize);
    EXPECT_EQ(size, push_source.OnMoreData(NULL, read_data.get(), size, 0));
    EXPECT_EQ(0, memcmp(data.get() + i, read_data.get(), size));
  }
  EXPECT_EQ(0u, push_source.UnProcessedBytes());

  push_source.OnClose(NULL);
}

// Validate that the SineWaveAudioSource writes the expected values for
// the FORMAT_16BIT_MONO. The values are carefully selected so rounding issues
// do not affect the result. We also test that AudioManager::GetLastMockBuffer
// works.
TEST(SimpleSources, SineWaveAudio16MonoTest) {
  const uint32 samples = 1024;
  const uint32 bytes_per_sample = 2;
  const int freq = 200;

  SineWaveAudioSource source(SineWaveAudioSource::FORMAT_16BIT_LINEAR_PCM, 1,
                             freq, AudioManager::kTelephoneSampleRate);

  AudioManager* audio_man = AudioManager::GetAudioManager();
  ASSERT_TRUE(NULL != audio_man);
  AudioOutputStream* oas =
      audio_man->MakeAudioStream(AudioManager::AUDIO_MOCK, 1,
                                 AudioManager::kTelephoneSampleRate,
                                 bytes_per_sample * 2);
  ASSERT_TRUE(NULL != oas);
  EXPECT_TRUE(oas->Open(samples * bytes_per_sample));

  oas->Start(&source);
  oas->Stop();
  oas->Close();

  ASSERT_TRUE(FakeAudioOutputStream::GetLastFakeStream());
  const int16* last_buffer =
      reinterpret_cast<int16*>(
          FakeAudioOutputStream::GetLastFakeStream()->buffer());
  ASSERT_TRUE(NULL != last_buffer);

  uint32 half_period = AudioManager::kTelephoneSampleRate / (freq * 2);

  // Spot test positive incursion of sine wave.
  EXPECT_EQ(0, last_buffer[0]);
  EXPECT_EQ(5126, last_buffer[1]);
  EXPECT_TRUE(last_buffer[1] < last_buffer[2]);
  EXPECT_TRUE(last_buffer[2] < last_buffer[3]);
  // Spot test negative incursion of sine wave.
  EXPECT_EQ(0, last_buffer[half_period]);
  EXPECT_EQ(-5126, last_buffer[half_period + 1]);
  EXPECT_TRUE(last_buffer[half_period + 1] > last_buffer[half_period + 2]);
  EXPECT_TRUE(last_buffer[half_period + 2] > last_buffer[half_period + 3]);
}
