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
  'targets': [
    {
      'target_name': 'starboard_base_symbolize',
      'type': 'static_library',
      'sources': [
        '<(DEPTH)/base/third_party/symbolize/demangle.cc',
        '<(DEPTH)/base/third_party/symbolize/symbolize.cc',
      ],
    },
    # Copy sources that we compile from the NDK so that we can reference them
    # by a relative path. Otherwise, without GYP pathname relativization
    # different configuration builds would clobber each other since they'd all
    # generate their .o at the same path in the NDK sources directory.
    {
      'target_name': 'ndk_sources',
      'type': 'none',
      'copies': [{
        'destination': '<(SHARED_INTERMEDIATE_DIR)/ndk-sources/',
        'files': [
          '<(NDK_HOME)/sources/android/native_app_glue/android_native_app_glue.c',
          '<(NDK_HOME)/sources/android/cpufeatures/cpu-features.c',
        ],
      }],
    },
    {
      'target_name': 'starboard_platform',
      'type': 'static_library',
      'sources': [
        'accessibility_get_text_to_speech_settings.cc',
        'application_android.cc',
        'atomic_public.h',
        'audio_decoder.cc',
        'audio_sink_get_max_channels.cc',
        'audio_sink_get_nearest_supported_sample_frequency.cc',
        'audio_sink_is_audio_frame_storage_type_supported.cc',
        'audio_sink_is_audio_sample_type_supported.cc',
        'configuration_public.h',
        'directory_close.cc',
        'directory_get_next.cc',
        'directory_open.cc',
        'file_can_open.cc',
        'file_close.cc',
        'file_delete.cc',
        'file_exists.cc',
        'file_flush.cc',
        'file_get_info.cc',
        'file_get_path_info.cc',
        'file_internal.cc',
        'file_open.cc',
        'file_read.cc',
        'file_seek.cc',
        'file_truncate.cc',
        'file_write.cc',
        'get_home_directory.cc',
        'input_event.cc',
        'jni_env_ext.cc',
        'log.cc',
        'log_flush.cc',
        'log_format.cc',
        'log_is_tty.cc',
        'log_raw.cc',
        'main.cc',
        'microphone_impl.cc',
        'opensles_audio_sink_type.cc',
        'opensles_audio_sink_type.h',
        'player_create.cc',
        'player_destroy.cc',
        'player_set_pause.cc',
        'player_set_volume.cc',
        'sanitizer_options.cc',
        'socket_get_local_interface_address.cc',
        'speech_synthesis_cancel.cc',
        'speech_synthesis_speak.cc',
        'system_get_connection_type.cc',
        'system_get_device_type.cc',
        'system_get_locale_id.cc',
        'system_get_path.cc',
        'system_get_property.cc',
        'system_get_stack.cc',
        'system_has_capability.cc',
        'system_platform_error.cc',
        'system_request_stop.cc',
        'thread_get_name.cc',
        'time_zone_get_dst_name.cc',
        'time_zone_get_name.cc',
        'video_decoder.cc',
        'video_window.cc',
        'window_create.cc',
        'window_destroy.cc',
        'window_get_platform_handle.cc',
        'window_get_size.cc',
        '<(SHARED_INTERMEDIATE_DIR)/ndk-sources/android_native_app_glue.c',
        '<(SHARED_INTERMEDIATE_DIR)/ndk-sources/cpu-features.c',
        '<(DEPTH)/starboard/shared/dlmalloc/memory_map.cc',
        '<(DEPTH)/starboard/shared/dlmalloc/memory_unmap.cc',
        '<(DEPTH)/starboard/shared/iso/character_is_alphanumeric.cc',
        '<(DEPTH)/starboard/shared/iso/character_is_digit.cc',
        '<(DEPTH)/starboard/shared/iso/character_is_hex_digit.cc',
        '<(DEPTH)/starboard/shared/iso/character_is_space.cc',
        '<(DEPTH)/starboard/shared/iso/character_is_upper.cc',
        '<(DEPTH)/starboard/shared/iso/character_to_lower.cc',
        '<(DEPTH)/starboard/shared/iso/character_to_upper.cc',
        '<(DEPTH)/starboard/shared/iso/double_absolute.cc',
        '<(DEPTH)/starboard/shared/iso/double_exponent.cc',
        '<(DEPTH)/starboard/shared/iso/double_floor.cc',
        '<(DEPTH)/starboard/shared/iso/double_is_finite.cc',
        '<(DEPTH)/starboard/shared/iso/double_is_nan.cc',
        '<(DEPTH)/starboard/shared/iso/memory_allocate_unchecked.cc',
        '<(DEPTH)/starboard/shared/iso/memory_compare.cc',
        '<(DEPTH)/starboard/shared/iso/memory_copy.cc',
        '<(DEPTH)/starboard/shared/iso/memory_find_byte.cc',
        '<(DEPTH)/starboard/shared/iso/memory_free.cc',
        '<(DEPTH)/starboard/shared/iso/memory_move.cc',
        '<(DEPTH)/starboard/shared/iso/memory_reallocate_unchecked.cc',
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
        '<(DEPTH)/starboard/shared/linux/byte_swap.cc',
        '<(DEPTH)/starboard/shared/linux/memory_get_stack_bounds.cc',
        '<(DEPTH)/starboard/shared/linux/page_internal.cc',
        '<(DEPTH)/starboard/shared/linux/system_get_random_data.cc',
        '<(DEPTH)/starboard/shared/linux/system_get_total_cpu_memory.cc',
        '<(DEPTH)/starboard/shared/linux/system_get_used_cpu_memory.cc',
        '<(DEPTH)/starboard/shared/linux/system_is_debugger_attached.cc',
        '<(DEPTH)/starboard/shared/linux/system_symbolize.cc',
        '<(DEPTH)/starboard/shared/linux/thread_get_id.cc',
        '<(DEPTH)/starboard/shared/linux/thread_set_name.cc',
        '<(DEPTH)/starboard/shared/nouser/user_get_current.cc',
        '<(DEPTH)/starboard/shared/nouser/user_get_property.cc',
        '<(DEPTH)/starboard/shared/nouser/user_get_signed_in.cc',
        '<(DEPTH)/starboard/shared/nouser/user_internal.cc',
        '<(DEPTH)/starboard/shared/posix/directory_create.cc',
        '<(DEPTH)/starboard/shared/posix/memory_allocate_aligned_unchecked.cc',
        '<(DEPTH)/starboard/shared/posix/memory_flush.cc',
        '<(DEPTH)/starboard/shared/posix/memory_free_aligned.cc',
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
        '<(DEPTH)/starboard/shared/posix/system_get_number_of_processors.cc',
        '<(DEPTH)/starboard/shared/posix/thread_sleep.cc',
        '<(DEPTH)/starboard/shared/posix/time_get_monotonic_now.cc',
        '<(DEPTH)/starboard/shared/posix/time_get_monotonic_thread_now.cc',
        '<(DEPTH)/starboard/shared/posix/time_get_now.cc',
        '<(DEPTH)/starboard/shared/posix/time_zone_get_current.cc',
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
        '<(DEPTH)/starboard/shared/starboard/media/media_can_play_mime_and_key_system.cc',
        '<(DEPTH)/starboard/shared/starboard/media/media_is_output_protected.cc',
        '<(DEPTH)/starboard/shared/starboard/media/media_set_output_protection.cc',
        '<(DEPTH)/starboard/shared/starboard/media/mime_type.cc',
        '<(DEPTH)/starboard/shared/starboard/media/mime_type.h',
        '<(DEPTH)/starboard/shared/starboard/microphone/microphone_close.cc',
        '<(DEPTH)/starboard/shared/starboard/microphone/microphone_create.cc',
        '<(DEPTH)/starboard/shared/starboard/microphone/microphone_destroy.cc',
        '<(DEPTH)/starboard/shared/starboard/microphone/microphone_get_available.cc',
        '<(DEPTH)/starboard/shared/starboard/microphone/microphone_internal.h',
        '<(DEPTH)/starboard/shared/starboard/microphone/microphone_is_sample_rate_supported.cc',
        '<(DEPTH)/starboard/shared/starboard/microphone/microphone_open.cc',
        '<(DEPTH)/starboard/shared/starboard/microphone/microphone_read.cc',
        '<(DEPTH)/starboard/shared/starboard/new.cc',
        '<(DEPTH)/starboard/shared/starboard/player/decoded_audio_internal.cc',
        '<(DEPTH)/starboard/shared/starboard/player/decoded_audio_internal.h',
        '<(DEPTH)/starboard/shared/starboard/player/filter/audio_decoder_internal.h',
        '<(DEPTH)/starboard/shared/starboard/player/filter/audio_renderer_internal.cc',
        '<(DEPTH)/starboard/shared/starboard/player/filter/audio_renderer_internal.h',
        '<(DEPTH)/starboard/shared/starboard/player/filter/filter_based_player_worker_handler.cc',
        '<(DEPTH)/starboard/shared/starboard/player/filter/filter_based_player_worker_handler.h',
        '<(DEPTH)/starboard/shared/starboard/player/filter/video_decoder_internal.h',
        '<(DEPTH)/starboard/shared/starboard/player/filter/video_renderer_internal.cc',
        '<(DEPTH)/starboard/shared/starboard/player/filter/video_renderer_internal.h',
        '<(DEPTH)/starboard/shared/starboard/player/input_buffer_internal.cc',
        '<(DEPTH)/starboard/shared/starboard/player/input_buffer_internal.h',
        '<(DEPTH)/starboard/shared/starboard/player/job_queue.cc',
        '<(DEPTH)/starboard/shared/starboard/player/job_queue.h',
        '<(DEPTH)/starboard/shared/starboard/player/player_get_info.cc',
        '<(DEPTH)/starboard/shared/starboard/player/player_internal.cc',
        '<(DEPTH)/starboard/shared/starboard/player/player_internal.h',
        '<(DEPTH)/starboard/shared/starboard/player/player_seek.cc',
        '<(DEPTH)/starboard/shared/starboard/player/player_set_bounds.cc',
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
        '<(DEPTH)/starboard/shared/starboard/window_set_default_options.cc',
        '<(DEPTH)/starboard/shared/stub/decode_target_create_egl.cc',
        '<(DEPTH)/starboard/shared/stub/decode_target_destroy.cc',
        '<(DEPTH)/starboard/shared/stub/decode_target_get_format.cc',
        '<(DEPTH)/starboard/shared/stub/decode_target_get_plane_egl.cc',
        '<(DEPTH)/starboard/shared/stub/decode_target_get_size.cc',
        '<(DEPTH)/starboard/shared/stub/decode_target_internal.h',
        '<(DEPTH)/starboard/shared/stub/decode_target_is_opaque.cc',
        '<(DEPTH)/starboard/shared/stub/drm_close_session.cc',
        '<(DEPTH)/starboard/shared/stub/drm_create_system.cc',
        '<(DEPTH)/starboard/shared/stub/drm_destroy_system.cc',
        '<(DEPTH)/starboard/shared/stub/drm_generate_session_update_request.cc',
        '<(DEPTH)/starboard/shared/stub/drm_system_internal.h',
        '<(DEPTH)/starboard/shared/stub/drm_update_session.cc',
        '<(DEPTH)/starboard/shared/stub/image_decode.cc',
        '<(DEPTH)/starboard/shared/stub/image_is_decode_supported.cc',
        '<(DEPTH)/starboard/shared/stub/media_get_audio_configuration.cc',
        '<(DEPTH)/starboard/shared/stub/media_get_audio_output_count.cc',
        '<(DEPTH)/starboard/shared/stub/media_is_supported.cc',
        '<(DEPTH)/starboard/shared/stub/system_get_total_gpu_memory.cc',
        '<(DEPTH)/starboard/shared/stub/system_get_used_gpu_memory.cc',
        '<(DEPTH)/starboard/shared/stub/system_hide_splash_screen.cc',
      ],
      'defines': [
        # This must be defined when building Starboard, and must not when
        # building Starboard client code.
        'STARBOARD_IMPLEMENTATION',
      ],
      'dependencies': [
        '<(DEPTH)/starboard/common/common.gyp:common',
        '<(DEPTH)/third_party/libevent/libevent.gyp:libevent',
        'starboard_base_symbolize',
      ],
    },
  ],
}
