// Copyright 2017 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

package dev.cobalt.media;

import android.media.AudioAttributes;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTimestamp;
import android.media.AudioTrack;
import android.os.Build;
import android.util.Log;
import dev.cobalt.util.UsedByNative;
import java.nio.ByteBuffer;

/** A wrapper of the android AudioTrack class. */
@UsedByNative
public class AudioTrackBridge {
  private AudioTrack audioTrack;
  private AudioTimestamp audioTimestamp = new AudioTimestamp();
  private long maxFramePositionSoFar = 0;

  public AudioTrackBridge(int sampleType, int sampleRate, int channelCount, int framesPerChannel) {
    int channelConfig;
    switch (channelCount) {
      case 1:
        channelConfig = AudioFormat.CHANNEL_OUT_MONO;
        break;
      case 2:
        channelConfig = AudioFormat.CHANNEL_OUT_STEREO;
        break;
      case 6:
        channelConfig = AudioFormat.CHANNEL_OUT_5POINT1;
        break;
      default:
        throw new RuntimeException("Unsupported channel count: " + channelCount);
    }

    AudioAttributes attributes =
        new AudioAttributes.Builder()
            .setContentType(AudioAttributes.CONTENT_TYPE_MUSIC)
            .setUsage(AudioAttributes.USAGE_MEDIA)
            .build();
    AudioFormat format =
        new AudioFormat.Builder()
            .setEncoding(sampleType)
            .setSampleRate(sampleRate)
            .setChannelMask(channelConfig)
            .build();

    int minBufferSizeBytes = AudioTrack.getMinBufferSize(sampleRate, channelConfig, sampleType);
    int audioTrackBufferSize = minBufferSizeBytes;
    // Use framesPerChannel to determine the buffer size.  To use a large buffer on a small
    // framesPerChannel may lead to audio playback not able to start.
    while (audioTrackBufferSize < framesPerChannel) {
      audioTrackBufferSize *= 2;
    }
    while (audioTrackBufferSize > 0) {
      try {
        audioTrack =
            new AudioTrack(
                attributes,
                format,
                audioTrackBufferSize,
                AudioTrack.MODE_STREAM,
                AudioManager.AUDIO_SESSION_ID_GENERATE);
      } catch (Exception e) {
        audioTrack = null;
      }
      // AudioTrack ctor can fail in multiple, platform specific ways, so do a thorough check
      // before proceed.
      if (audioTrack != null && audioTrack.getState() == AudioTrack.STATE_INITIALIZED) {
        break;
      }
      audioTrackBufferSize /= 2;
    }
    Log.i(
        "AudioTrack",
        String.format(
            "AudioTrack created with buffer size %d.  The minimum buffer size is %d.",
            audioTrackBufferSize, minBufferSizeBytes));
  }

  public void release() {
    audioTrack.release();
    audioTrack = null;
  }

  @SuppressWarnings("unused")
  @UsedByNative
  public int setVolume(float gain) {
    return audioTrack.setVolume(gain);
  }

  @SuppressWarnings("unused")
  @UsedByNative
  private void play() {
    audioTrack.play();
  }

  @SuppressWarnings("unused")
  @UsedByNative
  private void pause() {
    audioTrack.pause();
  }

  @SuppressWarnings("unused")
  @UsedByNative
  private void flush() {
    audioTrack.flush();
  }

  @SuppressWarnings("unused")
  @UsedByNative
  private int write(byte[] audioData, int sizeInBytes) {
    if (Build.VERSION.SDK_INT >= 23) {
      return audioTrack.write(audioData, 0, sizeInBytes, AudioTrack.WRITE_NON_BLOCKING);
    } else {
      ByteBuffer byteBuffer = ByteBuffer.wrap(audioData);
      return audioTrack.write(byteBuffer, sizeInBytes, AudioTrack.WRITE_NON_BLOCKING);
    }
  }

  @SuppressWarnings("unused")
  @UsedByNative
  private int write(float[] audioData, int sizeInFloats) {
    return audioTrack.write(audioData, 0, sizeInFloats, AudioTrack.WRITE_NON_BLOCKING);
  }

  @SuppressWarnings("unused")
  @UsedByNative
  private AudioTimestamp getAudioTimestamp() {
    // TODO: Consider calling with TIMEBASE_MONOTONIC and returning that
    // information to the starboard audio sink.
    if (audioTrack.getTimestamp(audioTimestamp)) {
      // This conversion is safe, as only the lower bits will be set, since we
      // called |getTimestamp| without a timebase.
      // https://developer.android.com/reference/android/media/AudioTimestamp.html#framePosition
      audioTimestamp.framePosition = (int) audioTimestamp.framePosition;
    } else {
      // Time stamps haven't been updated yet, assume playback hasn't started.
      audioTimestamp.framePosition = 0;
      audioTimestamp.nanoTime = System.nanoTime();
    }

    // TODO: This is required for correctness of the audio sink, because
    // otherwise we would be going back in time. Investigate the impact it has
    // on playback.  All empirical measurements so far suggest that it should
    // be negligible.
    if (audioTimestamp.framePosition < maxFramePositionSoFar) {
      audioTimestamp.framePosition = maxFramePositionSoFar;
    }
    maxFramePositionSoFar = audioTimestamp.framePosition;

    return audioTimestamp;
  }
}
