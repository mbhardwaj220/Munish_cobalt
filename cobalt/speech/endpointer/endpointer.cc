// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "cobalt/speech/endpointer/endpointer.h"

#include "base/time.h"

using base::Time;

namespace {
// Only send |kFrameSize| of audio data to energy endpointer each time.
// It should be smaller than the samples of audio bus which is passed in
// |ProcessAudio|.
const int kFrameSize = 160;
}

namespace cobalt {
namespace speech {

Endpointer::Endpointer(int sample_rate)
    : speech_input_possibly_complete_silence_length_us_(-1),
      speech_input_complete_silence_length_us_(-1),
      audio_frame_time_us_(0),
      sample_rate_(sample_rate),
      frame_rate_(sample_rate / kFrameSize) {
  Reset();

  speech_input_minimum_length_us_ =
      static_cast<int64_t>(1.7 * Time::kMicrosecondsPerSecond);
  speech_input_complete_silence_length_us_ =
      static_cast<int64_t>(0.5 * Time::kMicrosecondsPerSecond);
  long_speech_input_complete_silence_length_us_ = -1;
  long_speech_length_us_ = -1;
  speech_input_possibly_complete_silence_length_us_ =
      1 * Time::kMicrosecondsPerSecond;

  // Set the default configuration for Push To Talk mode.
  EnergyEndpointerParams ep_config;
  ep_config.set_frame_period(1.0f / static_cast<float>(frame_rate_));
  ep_config.set_frame_duration(1.0f / static_cast<float>(frame_rate_));
  ep_config.set_endpoint_margin(0.2f);
  ep_config.set_onset_window(0.15f);
  ep_config.set_speech_on_window(0.4f);
  ep_config.set_offset_window(0.15f);
  ep_config.set_onset_detect_dur(0.09f);
  ep_config.set_onset_confirm_dur(0.075f);
  ep_config.set_on_maintain_dur(0.10f);
  ep_config.set_offset_confirm_dur(0.12f);
  ep_config.set_decision_threshold(1000.0f);
  ep_config.set_min_decision_threshold(50.0f);
  ep_config.set_fast_update_dur(0.2f);
  ep_config.set_sample_rate(static_cast<float>(sample_rate));
  ep_config.set_min_fundamental_frequency(57.143f);
  ep_config.set_max_fundamental_frequency(400.0f);
  ep_config.set_contamination_rejection_period(0.25f);
  energy_endpointer_.Init(ep_config);
}

void Endpointer::Reset() {
  old_ep_status_ = EP_PRE_SPEECH;
  waiting_for_speech_possibly_complete_timeout_ = false;
  waiting_for_speech_complete_timeout_ = false;
  speech_previously_detected_ = false;
  speech_input_complete_ = false;
  audio_frame_time_us_ = 0;  // Reset time for packets sent to endpointer.
  speech_end_time_us_ = -1;
  speech_start_time_us_ = -1;
}

void Endpointer::StartSession() {
  Reset();
  energy_endpointer_.StartSession();
}

void Endpointer::EndSession() {
  energy_endpointer_.EndSession();
}

void Endpointer::SetEnvironmentEstimationMode() {
  Reset();
  energy_endpointer_.SetEnvironmentEstimationMode();
}

void Endpointer::SetUserInputMode() {
  energy_endpointer_.SetUserInputMode();
}

EpStatus Endpointer::Status(int64_t* time) {
  return energy_endpointer_.Status(time);
}

EpStatus Endpointer::ProcessAudio(
    const ShellAudioBus& audio_bus, float* rms_out) {
  DCHECK_EQ(audio_bus.channels(), 1);

  const size_t num_samples = audio_bus.frames();
  const int16_t* audio_data = NULL;

  ShellAudioBus int16_audio_bus(1, num_samples, ShellAudioBus::kInt16,
                                ShellAudioBus::kInterleaved);

  if (audio_bus.sample_type() == ShellAudioBus::kFloat32) {
    int16_audio_bus.Assign(audio_bus);
    DCHECK_EQ(int16_audio_bus.sample_type(), ShellAudioBus::kInt16);
    audio_data =
        reinterpret_cast<const int16_t*>(int16_audio_bus.interleaved_data());
  } else {
    DCHECK_EQ(audio_bus.sample_type(), ShellAudioBus::kInt16);
    audio_data =
        reinterpret_cast<const int16_t*>(audio_bus.interleaved_data());
  }

  EpStatus ep_status = EP_PRE_SPEECH;

  // Process the input data in blocks of kFrameSize, dropping any incomplete
  // frames at the end (which is ok since typically the caller will be recording
  // audio in multiples of our frame size).
  int sample_index = 0;
  while (static_cast<size_t>(sample_index + kFrameSize) <= num_samples) {
    // Have the endpointer process the frame.
    energy_endpointer_.ProcessAudioFrame(
        audio_frame_time_us_, audio_data + sample_index, kFrameSize, rms_out);
    sample_index += kFrameSize;
    audio_frame_time_us_ +=
        (kFrameSize * Time::kMicrosecondsPerSecond) / sample_rate_;

    // Get the status of the endpointer.
    int64_t ep_time;
    ep_status = energy_endpointer_.Status(&ep_time);

    // Handle state changes.
    if ((EP_SPEECH_PRESENT == ep_status) &&
        (EP_POSSIBLE_ONSET == old_ep_status_)) {
      speech_end_time_us_ = -1;
      waiting_for_speech_possibly_complete_timeout_ = false;
      waiting_for_speech_complete_timeout_ = false;
      // Trigger SpeechInputDidStart event on first detection.
      if (false == speech_previously_detected_) {
        speech_previously_detected_ = true;
        speech_start_time_us_ = ep_time;
      }
    }
    if ((EP_PRE_SPEECH == ep_status) &&
        (EP_POSSIBLE_OFFSET == old_ep_status_)) {
      speech_end_time_us_ = ep_time;
      waiting_for_speech_possibly_complete_timeout_ = true;
      waiting_for_speech_complete_timeout_ = true;
    }
    if (ep_time > speech_input_minimum_length_us_) {
      // Speech possibly complete timeout.
      if ((waiting_for_speech_possibly_complete_timeout_) &&
          (ep_time - speech_end_time_us_ >
              speech_input_possibly_complete_silence_length_us_)) {
        waiting_for_speech_possibly_complete_timeout_ = false;
      }
      if (waiting_for_speech_complete_timeout_) {
        // The length of the silence timeout period can be held constant, or it
        // can be changed after a fixed amount of time from the beginning of
        // speech.
        bool has_stepped_silence =
            (long_speech_length_us_ > 0) &&
            (long_speech_input_complete_silence_length_us_ > 0);
        int64_t requested_silence_length;
        if (has_stepped_silence &&
            (ep_time - speech_start_time_us_) > long_speech_length_us_) {
          requested_silence_length =
              long_speech_input_complete_silence_length_us_;
        } else {
          requested_silence_length =
              speech_input_complete_silence_length_us_;
        }

        // Speech complete timeout.
        if ((ep_time - speech_end_time_us_) > requested_silence_length) {
          waiting_for_speech_complete_timeout_ = false;
          speech_input_complete_ = true;
        }
      }
    }
    old_ep_status_ = ep_status;
  }
  return ep_status;
}

}  // namespace speech
}  // namespace cobalt
