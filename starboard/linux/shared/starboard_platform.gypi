# Copyright 2016 Google Inc. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
{
  'variables': {
    'starboard_platform_sources': [
      '<(DEPTH)/starboard/linux/shared/atomic_public.h',
      '<(DEPTH)/starboard/linux/shared/configuration_public.h',
      '<(DEPTH)/starboard/linux/shared/decode_target_get_info.cc',
      '<(DEPTH)/starboard/linux/shared/decode_target_internal.cc',
      '<(DEPTH)/starboard/linux/shared/decode_target_internal.h',
      '<(DEPTH)/starboard/linux/shared/decode_target_release.cc',
      '<(DEPTH)/starboard/linux/shared/media_is_video_supported.cc',
      '<(DEPTH)/starboard/linux/shared/player_components_impl.cc',
      '<(DEPTH)/starboard/linux/shared/system_get_connection_type.cc',
      '<(DEPTH)/starboard/linux/shared/system_get_device_type.cc',
      '<(DEPTH)/starboard/linux/shared/system_get_path.cc',
      '<(DEPTH)/starboard/linux/shared/system_has_capability.cc',
      '<(DEPTH)/starboard/shared/alsa/alsa_audio_sink_type.cc',
      '<(DEPTH)/starboard/shared/alsa/alsa_audio_sink_type.h',
      '<(DEPTH)/starboard/shared/alsa/alsa_util.cc',
      '<(DEPTH)/starboard/shared/alsa/alsa_util.h',
      '<(DEPTH)/starboard/shared/alsa/audio_sink_get_max_channels.cc',
      '<(DEPTH)/starboard/shared/alsa/audio_sink_get_nearest_supported_sample_frequency.cc',
      '<(DEPTH)/starboard/shared/alsa/audio_sink_is_audio_frame_storage_type_supported.cc',
      '<(DEPTH)/starboard/shared/alsa/audio_sink_is_audio_sample_type_supported.cc',
      '<(DEPTH)/starboard/shared/dlmalloc/memory_map.cc',
      '<(DEPTH)/starboard/shared/dlmalloc/memory_unmap.cc',
      '<(DEPTH)/starboard/shared/ffmpeg/ffmpeg_audio_decoder.cc',
      '<(DEPTH)/starboard/shared/ffmpeg/ffmpeg_audio_decoder.h',
      '<(DEPTH)/starboard/shared/ffmpeg/ffmpeg_audio_resampler.cc',
      '<(DEPTH)/starboard/shared/ffmpeg/ffmpeg_audio_resampler.h',
      '<(DEPTH)/starboard/shared/ffmpeg/ffmpeg_common.cc',
      '<(DEPTH)/starboard/shared/ffmpeg/ffmpeg_common.h',
      '<(DEPTH)/starboard/shared/ffmpeg/ffmpeg_video_decoder.cc',
      '<(DEPTH)/starboard/shared/ffmpeg/ffmpeg_video_decoder.h',
      '<(DEPTH)/starboard/shared/gcc/atomic_gcc_public.h',
      '<(DEPTH)/starboard/shared/iso/character_is_alphanumeric.cc',
      '<(DEPTH)/starboard/shared/iso/character_is_digit.cc',
      '<(DEPTH)/starboard/shared/iso/character_is_hex_digit.cc',
      '<(DEPTH)/starboard/shared/iso/character_is_space.cc',
      '<(DEPTH)/starboard/shared/iso/character_is_upper.cc',
      '<(DEPTH)/starboard/shared/iso/character_to_lower.cc',
      '<(DEPTH)/starboard/shared/iso/character_to_upper.cc',
      '<(DEPTH)/starboard/shared/iso/directory_close.cc',
      '<(DEPTH)/starboard/shared/iso/directory_get_next.cc',
      '<(DEPTH)/starboard/shared/iso/directory_open.cc',
      '<(DEPTH)/starboard/shared/iso/double_absolute.cc',
      '<(DEPTH)/starboard/shared/iso/double_exponent.cc',
      '<(DEPTH)/starboard/shared/iso/double_floor.cc',
      '<(DEPTH)/starboard/shared/iso/double_is_finite.cc',
      '<(DEPTH)/starboard/shared/iso/double_is_nan.cc',
      '<(DEPTH)/starboard/shared/iso/memory_compare.cc',
      '<(DEPTH)/starboard/shared/iso/memory_copy.cc',
      '<(DEPTH)/starboard/shared/iso/memory_find_byte.cc',
      '<(DEPTH)/starboard/shared/iso/memory_move.cc',
      '<(DEPTH)/starboard/shared/iso/memory_set.cc',
      '<(DEPTH)/starboard/shared/iso/string_compare.cc',
      '<(DEPTH)/starboard/shared/iso/string_compare_all.cc',
      '<(DEPTH)/starboard/shared/iso/string_find_character.cc',
      '<(DEPTH)/starboard/shared/iso/string_find_last_character.cc',
      '<(DEPTH)/starboard/shared/iso/string_find_string.cc',
      '<(DEPTH)/starboard/shared/iso/string_get_length.cc',
      '<(DEPTH)/starboard/shared/iso/string_get_length_wide.cc',
      '<(DEPTH)/starboard/shared/iso/string_parse_double.cc',
      '<(DEPTH)/starboard/shared/iso/string_parse_signed_integer.cc',
      '<(DEPTH)/starboard/shared/iso/string_parse_uint64.cc',
      '<(DEPTH)/starboard/shared/iso/string_parse_unsigned_integer.cc',
      '<(DEPTH)/starboard/shared/iso/string_scan.cc',
      '<(DEPTH)/starboard/shared/iso/system_binary_search.cc',
      '<(DEPTH)/starboard/shared/iso/system_sort.cc',
      '<(DEPTH)/starboard/shared/libevent/socket_waiter_add.cc',
      '<(DEPTH)/starboard/shared/libevent/socket_waiter_create.cc',
      '<(DEPTH)/starboard/shared/libevent/socket_waiter_destroy.cc',
      '<(DEPTH)/starboard/shared/libevent/socket_waiter_internal.cc',
      '<(DEPTH)/starboard/shared/libevent/socket_waiter_remove.cc',
      '<(DEPTH)/starboard/shared/libevent/socket_waiter_wait.cc',
      '<(DEPTH)/starboard/shared/libevent/socket_waiter_wait_timed.cc',
      '<(DEPTH)/starboard/shared/libevent/socket_waiter_wake_up.cc',
      '<(DEPTH)/starboard/shared/libvpx/vpx_video_decoder.cc',
      '<(DEPTH)/starboard/shared/libvpx/vpx_video_decoder.h',
      '<(DEPTH)/starboard/shared/linux/byte_swap.cc',
      '<(DEPTH)/starboard/shared/linux/get_home_directory.cc',
      '<(DEPTH)/starboard/shared/linux/memory_get_stack_bounds.cc',
      '<(DEPTH)/starboard/shared/linux/page_internal.cc',
      '<(DEPTH)/starboard/shared/linux/socket_get_interface_address.cc',
      '<(DEPTH)/starboard/shared/linux/system_get_random_data.cc',
      '<(DEPTH)/starboard/shared/linux/system_get_stack.cc',
      '<(DEPTH)/starboard/shared/linux/system_get_total_cpu_memory.cc',
      '<(DEPTH)/starboard/shared/linux/system_get_used_cpu_memory.cc',
      '<(DEPTH)/starboard/shared/linux/system_is_debugger_attached.cc',
      '<(DEPTH)/starboard/shared/linux/system_symbolize.cc',
      '<(DEPTH)/starboard/shared/linux/thread_get_id.cc',
      '<(DEPTH)/starboard/shared/linux/thread_get_name.cc',
      '<(DEPTH)/starboard/shared/linux/thread_set_name.cc',
      '<(DEPTH)/starboard/shared/nouser/user_get_current.cc',
      '<(DEPTH)/starboard/shared/nouser/user_get_property.cc',
      '<(DEPTH)/starboard/shared/nouser/user_get_signed_in.cc',
      '<(DEPTH)/starboard/shared/nouser/user_internal.cc',
      '<(DEPTH)/starboard/shared/posix/directory_create.cc',
      '<(DEPTH)/starboard/shared/posix/file_can_open.cc',
      '<(DEPTH)/starboard/shared/posix/file_close.cc',
      '<(DEPTH)/starboard/shared/posix/file_delete.cc',
      '<(DEPTH)/starboard/shared/posix/file_exists.cc',
      '<(DEPTH)/starboard/shared/posix/file_flush.cc',
      '<(DEPTH)/starboard/shared/posix/file_get_info.cc',
      '<(DEPTH)/starboard/shared/posix/file_get_path_info.cc',
      '<(DEPTH)/starboard/shared/posix/file_open.cc',
      '<(DEPTH)/starboard/shared/posix/file_read.cc',
      '<(DEPTH)/starboard/shared/posix/file_seek.cc',
      '<(DEPTH)/starboard/shared/posix/file_truncate.cc',
      '<(DEPTH)/starboard/shared/posix/file_write.cc',
      '<(DEPTH)/starboard/shared/posix/log.cc',
      '<(DEPTH)/starboard/shared/posix/log_flush.cc',
      '<(DEPTH)/starboard/shared/posix/log_format.cc',
      '<(DEPTH)/starboard/shared/posix/log_is_tty.cc',
      '<(DEPTH)/starboard/shared/posix/log_raw.cc',
      '<(DEPTH)/starboard/shared/posix/memory_flush.cc',
      '<(DEPTH)/starboard/shared/posix/set_non_blocking_internal.cc',
      '<(DEPTH)/starboard/shared/posix/socket_accept.cc',
      '<(DEPTH)/starboard/shared/posix/socket_bind.cc',
      '<(DEPTH)/starboard/shared/posix/socket_clear_last_error.cc',
      '<(DEPTH)/starboard/shared/posix/socket_connect.cc',
      '<(DEPTH)/starboard/shared/posix/socket_create.cc',
      '<(DEPTH)/starboard/shared/posix/socket_destroy.cc',
      '<(DEPTH)/starboard/shared/posix/socket_free_resolution.cc',
      '<(DEPTH)/starboard/shared/posix/socket_get_last_error.cc',
      '<(DEPTH)/starboard/shared/posix/socket_get_local_address.cc',
      '<(DEPTH)/starboard/shared/posix/socket_internal.cc',
      '<(DEPTH)/starboard/shared/posix/socket_is_connected.cc',
      '<(DEPTH)/starboard/shared/posix/socket_is_connected_and_idle.cc',
      '<(DEPTH)/starboard/shared/posix/socket_join_multicast_group.cc',
      '<(DEPTH)/starboard/shared/posix/socket_listen.cc',
      '<(DEPTH)/starboard/shared/posix/socket_receive_from.cc',
      '<(DEPTH)/starboard/shared/posix/socket_resolve.cc',
      '<(DEPTH)/starboard/shared/posix/socket_send_to.cc',
      '<(DEPTH)/starboard/shared/posix/socket_set_broadcast.cc',
      '<(DEPTH)/starboard/shared/posix/socket_set_receive_buffer_size.cc',
      '<(DEPTH)/starboard/shared/posix/socket_set_reuse_address.cc',
      '<(DEPTH)/starboard/shared/posix/socket_set_send_buffer_size.cc',
      '<(DEPTH)/starboard/shared/posix/socket_set_tcp_keep_alive.cc',
      '<(DEPTH)/starboard/shared/posix/socket_set_tcp_no_delay.cc',
      '<(DEPTH)/starboard/shared/posix/socket_set_tcp_window_scaling.cc',
      '<(DEPTH)/starboard/shared/posix/string_compare_no_case.cc',
      '<(DEPTH)/starboard/shared/posix/string_compare_no_case_n.cc',
      '<(DEPTH)/starboard/shared/posix/string_compare_wide.cc',
      '<(DEPTH)/starboard/shared/posix/string_format.cc',
      '<(DEPTH)/starboard/shared/posix/string_format_wide.cc',
      '<(DEPTH)/starboard/shared/posix/system_break_into_debugger.cc',
      '<(DEPTH)/starboard/shared/posix/system_clear_last_error.cc',
      '<(DEPTH)/starboard/shared/posix/system_get_error_string.cc',
      '<(DEPTH)/starboard/shared/posix/system_get_last_error.cc',
      '<(DEPTH)/starboard/shared/posix/system_get_locale_id.cc',
      '<(DEPTH)/starboard/shared/posix/system_get_number_of_processors.cc',
      '<(DEPTH)/starboard/shared/posix/thread_sleep.cc',
      '<(DEPTH)/starboard/shared/posix/time_get_monotonic_now.cc',
      '<(DEPTH)/starboard/shared/posix/time_get_monotonic_thread_now.cc',
      '<(DEPTH)/starboard/shared/posix/time_get_now.cc',
      '<(DEPTH)/starboard/shared/posix/time_zone_get_current.cc',
      '<(DEPTH)/starboard/shared/posix/time_zone_get_dst_name.cc',
      '<(DEPTH)/starboard/shared/posix/time_zone_get_name.cc',
      '<(DEPTH)/starboard/shared/pthread/condition_variable_broadcast.cc',
      '<(DEPTH)/starboard/shared/pthread/condition_variable_create.cc',
      '<(DEPTH)/starboard/shared/pthread/condition_variable_destroy.cc',
      '<(DEPTH)/starboard/shared/pthread/condition_variable_signal.cc',
      '<(DEPTH)/starboard/shared/pthread/condition_variable_wait.cc',
      '<(DEPTH)/starboard/shared/pthread/condition_variable_wait_timed.cc',
      '<(DEPTH)/starboard/shared/pthread/mutex_acquire.cc',
      '<(DEPTH)/starboard/shared/pthread/mutex_acquire_try.cc',
      '<(DEPTH)/starboard/shared/pthread/mutex_create.cc',
      '<(DEPTH)/starboard/shared/pthread/mutex_destroy.cc',
      '<(DEPTH)/starboard/shared/pthread/mutex_release.cc',
      '<(DEPTH)/starboard/shared/pthread/once.cc',
      '<(DEPTH)/starboard/shared/pthread/thread_create.cc',
      '<(DEPTH)/starboard/shared/pthread/thread_create_local_key.cc',
      '<(DEPTH)/starboard/shared/pthread/thread_create_priority.h',
      '<(DEPTH)/starboard/shared/pthread/thread_destroy_local_key.cc',
      '<(DEPTH)/starboard/shared/pthread/thread_detach.cc',
      '<(DEPTH)/starboard/shared/pthread/thread_get_current.cc',
      '<(DEPTH)/starboard/shared/pthread/thread_get_local_value.cc',
      '<(DEPTH)/starboard/shared/pthread/thread_is_equal.cc',
      '<(DEPTH)/starboard/shared/pthread/thread_join.cc',
      '<(DEPTH)/starboard/shared/pthread/thread_set_local_value.cc',
      '<(DEPTH)/starboard/shared/pthread/thread_yield.cc',
      '<(DEPTH)/starboard/shared/signal/crash_signals.h',
      '<(DEPTH)/starboard/shared/signal/crash_signals_sigaction.cc',
      '<(DEPTH)/starboard/shared/signal/suspend_signals.cc',
      '<(DEPTH)/starboard/shared/signal/suspend_signals.h',
      '<(DEPTH)/starboard/shared/starboard/application.cc',
      '<(DEPTH)/starboard/shared/starboard/audio_sink/audio_sink_create.cc',
      '<(DEPTH)/starboard/shared/starboard/audio_sink/audio_sink_destroy.cc',
      '<(DEPTH)/starboard/shared/starboard/audio_sink/audio_sink_internal.cc',
      '<(DEPTH)/starboard/shared/starboard/audio_sink/audio_sink_internal.h',
      '<(DEPTH)/starboard/shared/starboard/audio_sink/audio_sink_is_valid.cc',
      '<(DEPTH)/starboard/shared/starboard/audio_sink/stub_audio_sink_type.cc',
      '<(DEPTH)/starboard/shared/starboard/audio_sink/stub_audio_sink_type.h',
      '<(DEPTH)/starboard/shared/starboard/command_line.cc',
      '<(DEPTH)/starboard/shared/starboard/command_line.h',
      '<(DEPTH)/starboard/shared/starboard/directory_can_open.cc',
      '<(DEPTH)/starboard/shared/starboard/event_cancel.cc',
      '<(DEPTH)/starboard/shared/starboard/event_schedule.cc',
      '<(DEPTH)/starboard/shared/starboard/file_mode_string_to_flags.cc',
      '<(DEPTH)/starboard/shared/starboard/file_storage/storage_close_record.cc',
      '<(DEPTH)/starboard/shared/starboard/file_storage/storage_delete_record.cc',
      '<(DEPTH)/starboard/shared/starboard/file_storage/storage_get_record_size.cc',
      '<(DEPTH)/starboard/shared/starboard/file_storage/storage_open_record.cc',
      '<(DEPTH)/starboard/shared/starboard/file_storage/storage_read_record.cc',
      '<(DEPTH)/starboard/shared/starboard/file_storage/storage_write_record.cc',
      '<(DEPTH)/starboard/shared/starboard/log_message.cc',
      '<(DEPTH)/starboard/shared/starboard/log_raw_dump_stack.cc',
      '<(DEPTH)/starboard/shared/starboard/log_raw_format.cc',
      '<(DEPTH)/starboard/shared/starboard/media/codec_util.cc',
      '<(DEPTH)/starboard/shared/starboard/media/codec_util.h',
      '<(DEPTH)/starboard/shared/starboard/media/media_can_play_mime_and_key_system.cc',
      '<(DEPTH)/starboard/shared/starboard/media/media_get_audio_configuration_stereo_only.cc',
      '<(DEPTH)/starboard/shared/starboard/media/media_get_audio_output_count_stereo_only.cc',
      '<(DEPTH)/starboard/shared/starboard/media/media_is_audio_supported_aac_and_opus.cc',
      '<(DEPTH)/starboard/shared/starboard/media/media_is_output_protected.cc',
      '<(DEPTH)/starboard/shared/starboard/media/media_set_output_protection.cc',
      '<(DEPTH)/starboard/shared/starboard/media/media_util.cc',
      '<(DEPTH)/starboard/shared/starboard/media/media_util.h',
      '<(DEPTH)/starboard/shared/starboard/media/mime_type.cc',
      '<(DEPTH)/starboard/shared/starboard/media/mime_type.h',
      '<(DEPTH)/starboard/shared/starboard/new.cc',
      '<(DEPTH)/starboard/shared/starboard/player/decoded_audio_internal.cc',
      '<(DEPTH)/starboard/shared/starboard/player/decoded_audio_internal.h',
      '<(DEPTH)/starboard/shared/starboard/player/filter/audio_decoder_internal.h',
      '<(DEPTH)/starboard/shared/starboard/player/filter/audio_frame_tracker.h',
      '<(DEPTH)/starboard/shared/starboard/player/filter/audio_renderer_impl_internal.cc',
      '<(DEPTH)/starboard/shared/starboard/player/filter/audio_renderer_impl_internal.h',
      '<(DEPTH)/starboard/shared/starboard/player/filter/audio_renderer_internal.h',
      '<(DEPTH)/starboard/shared/starboard/player/filter/audio_time_stretcher.cc',
      '<(DEPTH)/starboard/shared/starboard/player/filter/audio_time_stretcher.h',
      '<(DEPTH)/starboard/shared/starboard/player/filter/decoded_audio_queue.cc',
      '<(DEPTH)/starboard/shared/starboard/player/filter/decoded_audio_queue.h',
      '<(DEPTH)/starboard/shared/starboard/player/filter/filter_based_player_worker_handler.cc',
      '<(DEPTH)/starboard/shared/starboard/player/filter/filter_based_player_worker_handler.h',
      '<(DEPTH)/starboard/shared/starboard/player/filter/player_components.h',
      '<(DEPTH)/starboard/shared/starboard/player/filter/video_decoder_internal.h',
      '<(DEPTH)/starboard/shared/starboard/player/filter/video_renderer_impl_internal.cc',
      '<(DEPTH)/starboard/shared/starboard/player/filter/video_renderer_impl_internal.h',
      '<(DEPTH)/starboard/shared/starboard/player/filter/video_renderer_internal.h',
      '<(DEPTH)/starboard/shared/starboard/player/filter/wsola_internal.cc',
      '<(DEPTH)/starboard/shared/starboard/player/filter/wsola_internal.h',
      '<(DEPTH)/starboard/shared/starboard/player/input_buffer_internal.cc',
      '<(DEPTH)/starboard/shared/starboard/player/input_buffer_internal.h',
      '<(DEPTH)/starboard/shared/starboard/player/job_queue.cc',
      '<(DEPTH)/starboard/shared/starboard/player/job_queue.h',
      '<(DEPTH)/starboard/shared/starboard/player/player_create.cc',
      '<(DEPTH)/starboard/shared/starboard/player/player_destroy.cc',
      '<(DEPTH)/starboard/shared/starboard/player/player_get_current_frame.cc',
      '<(DEPTH)/starboard/shared/starboard/player/player_get_info.cc',
      '<(DEPTH)/starboard/shared/starboard/player/player_internal.cc',
      '<(DEPTH)/starboard/shared/starboard/player/player_internal.h',
      '<(DEPTH)/starboard/shared/starboard/player/player_output_mode_supported.cc',
      '<(DEPTH)/starboard/shared/starboard/player/player_seek.cc',
      '<(DEPTH)/starboard/shared/starboard/player/player_set_bounds.cc',
      '<(DEPTH)/starboard/shared/starboard/player/player_set_playback_rate.cc',
      '<(DEPTH)/starboard/shared/starboard/player/player_set_volume.cc',
      '<(DEPTH)/starboard/shared/starboard/player/player_worker.cc',
      '<(DEPTH)/starboard/shared/starboard/player/player_worker.h',
      '<(DEPTH)/starboard/shared/starboard/player/player_write_end_of_stream.cc',
      '<(DEPTH)/starboard/shared/starboard/player/player_write_sample.cc',
      '<(DEPTH)/starboard/shared/starboard/player/video_frame_internal.cc',
      '<(DEPTH)/starboard/shared/starboard/player/video_frame_internal.h',
      '<(DEPTH)/starboard/shared/starboard/queue_application.cc',
      '<(DEPTH)/starboard/shared/starboard/string_concat.cc',
      '<(DEPTH)/starboard/shared/starboard/string_concat_wide.cc',
      '<(DEPTH)/starboard/shared/starboard/string_copy.cc',
      '<(DEPTH)/starboard/shared/starboard/string_copy_wide.cc',
      '<(DEPTH)/starboard/shared/starboard/string_duplicate.cc',
      '<(DEPTH)/starboard/shared/starboard/system_get_random_uint64.cc',
      '<(DEPTH)/starboard/shared/starboard/system_request_pause.cc',
      '<(DEPTH)/starboard/shared/starboard/system_request_stop.cc',
      '<(DEPTH)/starboard/shared/starboard/system_request_suspend.cc',
      '<(DEPTH)/starboard/shared/starboard/system_request_unpause.cc',
      '<(DEPTH)/starboard/shared/starboard/window_set_default_options.cc',
      '<(DEPTH)/starboard/shared/stub/accessibility_get_display_settings.cc',
      '<(DEPTH)/starboard/shared/stub/accessibility_get_text_to_speech_settings.cc',
      '<(DEPTH)/starboard/shared/stub/cryptography_create_transformer.cc',
      '<(DEPTH)/starboard/shared/stub/cryptography_destroy_transformer.cc',
      '<(DEPTH)/starboard/shared/stub/cryptography_get_tag.cc',
      '<(DEPTH)/starboard/shared/stub/cryptography_set_authenticated_data.cc',
      '<(DEPTH)/starboard/shared/stub/cryptography_set_initialization_vector.cc',
      '<(DEPTH)/starboard/shared/stub/cryptography_transform.cc',
      '<(DEPTH)/starboard/shared/stub/drm_close_session.cc',
      '<(DEPTH)/starboard/shared/stub/drm_create_system.cc',
      '<(DEPTH)/starboard/shared/stub/drm_destroy_system.cc',
      '<(DEPTH)/starboard/shared/stub/drm_generate_session_update_request.cc',
      '<(DEPTH)/starboard/shared/stub/drm_system_internal.h',
      '<(DEPTH)/starboard/shared/stub/drm_update_session.cc',
      '<(DEPTH)/starboard/shared/stub/image_decode.cc',
      '<(DEPTH)/starboard/shared/stub/image_is_decode_supported.cc',
      '<(DEPTH)/starboard/shared/stub/media_is_supported.cc',
      '<(DEPTH)/starboard/shared/stub/media_is_transfer_characteristics_supported.cc',
      '<(DEPTH)/starboard/shared/stub/microphone_close.cc',
      '<(DEPTH)/starboard/shared/stub/microphone_create.cc',
      '<(DEPTH)/starboard/shared/stub/microphone_destroy.cc',
      '<(DEPTH)/starboard/shared/stub/microphone_get_available.cc',
      '<(DEPTH)/starboard/shared/stub/microphone_is_sample_rate_supported.cc',
      '<(DEPTH)/starboard/shared/stub/microphone_open.cc',
      '<(DEPTH)/starboard/shared/stub/microphone_read.cc',
      '<(DEPTH)/starboard/shared/stub/system_clear_platform_error.cc',
      '<(DEPTH)/starboard/shared/stub/system_get_total_gpu_memory.cc',
      '<(DEPTH)/starboard/shared/stub/system_get_used_gpu_memory.cc',
      '<(DEPTH)/starboard/shared/stub/system_hide_splash_screen.cc',
      '<(DEPTH)/starboard/shared/stub/system_raise_platform_error.cc',
    ],
    'conditions': [
      ['use_dlmalloc_allocator==1', {
        'starboard_platform_sources': [
          '<(DEPTH)/starboard/shared/dlmalloc/memory_allocate_aligned_unchecked.cc',
          '<(DEPTH)/starboard/shared/dlmalloc/memory_allocate_unchecked.cc',
          '<(DEPTH)/starboard/shared/dlmalloc/memory_free.cc',
          '<(DEPTH)/starboard/shared/dlmalloc/memory_free_aligned.cc',
          '<(DEPTH)/starboard/shared/dlmalloc/memory_reallocate_unchecked.cc',
        ],
      }, {
        'starboard_platform_sources': [
          '<(DEPTH)/starboard/shared/iso/memory_allocate_unchecked.cc',
          '<(DEPTH)/starboard/shared/iso/memory_free.cc',
          '<(DEPTH)/starboard/shared/iso/memory_reallocate_unchecked.cc',
          '<(DEPTH)/starboard/shared/posix/memory_allocate_aligned_unchecked.cc',
          '<(DEPTH)/starboard/shared/posix/memory_free_aligned.cc',
        ],
      }]
    ],
    'starboard_platform_dependencies': [
      '<(DEPTH)/starboard/common/common.gyp:common',
      '<(DEPTH)/starboard/linux/shared/starboard_base_symbolize.gyp:starboard_base_symbolize',
      '<(DEPTH)/third_party/dlmalloc/dlmalloc.gyp:dlmalloc',
      '<(DEPTH)/third_party/libevent/libevent.gyp:libevent',
      '<(DEPTH)/third_party/libvpx/libvpx.gyp:libvpx',
    ],
  },
}
