# Copyright (c) 2012 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
  'target_defaults': {
    'variables': {
      'base_target': 0,
    },
    'target_conditions': [
      # This part is shared between the targets defined below.
      ['base_target==1', {
        'sources': [
          '<(DEPTH)/build/build_config.h',
          'allocator/allocator_extension.cc',
          'allocator/allocator_extension.h',
          'allocator/type_profiler_control.cc',
          'allocator/type_profiler_control.h',
          'at_exit.cc',
          'at_exit.h',
          'atomic_ref_count.h',
          'atomic_sequence_num.h',
          'atomicops.h',
          'atomicops_internals_starboard.h',
          'atomicops_internals_tsan.h',
          'base64.cc',
          'base64.h',
          'base_export.h',
          'base_paths.cc',
          'base_paths.h',
          'base_paths_starboard.cc',
          'base_switches.h',
          'basictypes.h',
          'bind.h',
          'bind_helpers.cc',
          'bind_helpers.h',
          'bind_internal.h',
          'bind_internal_functor.h',
          'bits.h',
          'build_time.cc',
          'build_time.h',
          'callback.h',
          'callback_helpers.h',
          'callback_internal.cc',
          'callback_internal.h',
          'cancelable_callback.h',
          'circular_buffer_shell.cc',
          'circular_buffer_shell.h',
          'command_line.cc',
          'command_line.h',
          'compiler_specific.h',
          'containers/linked_hash_map.h',
          'containers/linked_list.h',
          'containers/mru_cache.h',
          'containers/small_map.h',
          'containers/stack_container.h',
          'cpu.cc',
          'cpu.h',
          'critical_closure.h',
          'debug/alias.cc',
          'debug/alias.h',
          'debug/debugger.cc',
          'debug/debugger.h',
          'debug/debugger_starboard.cc',
          # This file depends on files from the 'allocator' target,
          # but this target does not depend on 'allocator' (see
          # allocator.gyp for details).
          'debug/leak_annotations.h',
          'debug/leak_tracker.h',
          'debug/profiler.cc',
          'debug/profiler.h',
          'debug/stack_trace.cc',
          'debug/stack_trace.h',
          'debug/stack_trace_starboard.cc',
          'debug/trace_event.cc',
          'debug/trace_event.h',
          'debug/trace_event_impl.cc',
          'debug/trace_event_impl.h',
          'file_path.cc',
          'file_path.h',
          'file_util.cc',
          'file_util.h',
          'file_util_proxy.cc',
          'file_util_proxy.h',
          'file_util_starboard.cc',
          'file_version_info.h',
          'files/dir_reader_dirent.h',
          'files/dir_reader_fallback.h',
          'files/scoped_temp_dir.cc',
          'files/scoped_temp_dir.h',
          'float_util.h',
          'format_macros.h',
          'gtest_prod_util.h',
          'guid.cc',
          'guid.h',
          'guid_posix.cc',
          'guid_starboard.cc',
          'hash.cc',
          'hash.h',
          'hash_tables.h',
          'hi_res_timer_manager.h',
          'id_map.h',
          'ios/device_util.h',
          'ios/device_util.mm',
          'ios/ios_util.h',
          'ios/ios_util.mm',
          'ios/scoped_critical_action.h',
          'ios/scoped_critical_action.mm',
          'json/json_file_value_serializer.cc',
          'json/json_file_value_serializer.h',
          'json/json_parser.cc',
          'json/json_parser.h',
          'json/json_reader.cc',
          'json/json_reader.h',
          'json/json_string_value_serializer.cc',
          'json/json_string_value_serializer.h',
          'json/json_value_converter.h',
          'json/json_writer.cc',
          'json/json_writer.h',
          'json/string_escape.cc',
          'json/string_escape.h',
          'lazy_instance.cc',
          'lazy_instance.h',
          'location.cc',
          'location.h',
          'logging.cc',
          'logging.h',
          'memory/aligned_memory.cc',
          'memory/aligned_memory.h',
          'memory/linked_ptr.h',
          'memory/manual_constructor.h',
          'memory/raw_scoped_refptr_mismatch_checker.h',
          'memory/ref_counted.cc',
          'memory/ref_counted.h',
          'memory/ref_counted_memory.cc',
          'memory/ref_counted_memory.h',
          'memory/scoped_handle.h',
          'memory/scoped_nsobject.h',
          'memory/scoped_open_process.h',
          'memory/scoped_policy.h',
          'memory/scoped_ptr.h',
          'memory/scoped_vector.h',
          'memory/singleton.cc',
          'memory/singleton.h',
          'memory/weak_ptr.cc',
          'memory/weak_ptr.h',
          'message_loop.cc',
          'message_loop.h',
          'message_loop_proxy.cc',
          'message_loop_proxy.h',
          'message_loop_proxy_impl.cc',
          'message_loop_proxy_impl.h',
          'message_pump.cc',
          'message_pump.h',
          'message_pump_default.cc',
          'message_pump_default.h',
          'message_pump_io_starboard.cc',
          'message_pump_io_starboard.h',
          'message_pump_ui_starboard.cc',
          'message_pump_ui_starboard.h',
          'metrics/bucket_ranges.cc',
          'metrics/bucket_ranges.h',
          'metrics/histogram.cc',
          'metrics/histogram.h',
          'metrics/histogram_base.cc',
          'metrics/histogram_base.h',
          'metrics/histogram_flattener.h',
          'metrics/histogram_samples.cc',
          'metrics/histogram_samples.h',
          'metrics/histogram_snapshot_manager.cc',
          'metrics/histogram_snapshot_manager.h',
          'metrics/sample_map.cc',
          'metrics/sample_map.h',
          'metrics/sample_vector.cc',
          'metrics/sample_vector.h',
          'metrics/sparse_histogram.cc',
          'metrics/sparse_histogram.h',
          'metrics/statistics_recorder.cc',
          'metrics/statistics_recorder.h',
          'metrics/stats_counters.cc',
          'metrics/stats_counters.h',
          'move.h',
          'native_library.h',
          'observer_list.h',
          'observer_list_threadsafe.h',
          'optional.h',
          'path_service.cc',
          'path_service.h',
          'pending_task.cc',
          'pending_task.h',
          'pickle.cc',
          'pickle.h',
          'platform_file.cc',
          'platform_file.h',
          'platform_file_starboard.cc',
          'port.h',
          'posix/eintr_wrapper.h',
          'process.h',
          'process_starboard.cc',
          'process_util.h',
          'process_util_starboard.cc',
          'profiler/alternate_timer.cc',
          'profiler/alternate_timer.h',
          'profiler/scoped_profile.cc',
          'profiler/scoped_profile.h',
          'profiler/tracked_time.cc',
          'profiler/tracked_time.h',
          'rand_util.cc',
          'rand_util.h',
          'rand_util_starboard.cc',
          'run_loop.cc',
          'run_loop.h',
          'sequenced_task_runner.cc',
          'sequenced_task_runner.h',
          'sequenced_task_runner_helpers.h',
          'sha1.h',
          'sha1_portable.cc',
          'single_thread_task_runner.h',
          'state_machine_shell.h',
          'stl_util.h',
          'string16.cc',
          'string16.h',
          'string_number_conversions.cc',
          'string_number_conversions.h',
          'string_piece.cc',
          'string_piece.h',
          'string_split.cc',
          'string_split.h',
          'string_tokenizer.h',
          'string_util.cc',
          'string_util.h',
          'stringize_macros.h',
          'stringprintf.cc',
          'stringprintf.h',
          'supports_user_data.cc',
          'supports_user_data.h',
          'synchronization/cancellation_flag.cc',
          'synchronization/cancellation_flag.h',
          'synchronization/condition_variable.h',
          'synchronization/condition_variable_starboard.cc',
          'synchronization/lock.cc',
          'synchronization/lock.h',
          'synchronization/lock_impl.h',
          'synchronization/lock_impl_starboard.cc',
          'synchronization/waitable_event.h',
          'synchronization/waitable_event_starboard.cc',
          'sys_byteorder.h',
          'sys_info.cc',
          'sys_info.h',
          'sys_info_starboard.cc',
          'sys_string_conversions.h',
          'sys_string_conversions_starboard.cc',
          'system_monitor/system_monitor.cc',
          'system_monitor/system_monitor.h',
          'system_monitor/system_monitor_starboard.cc',
          'task_runner.cc',
          'task_runner.h',
          'task_runner_util.h',
          'template_util.h',
          'third_party/dmg_fp/dmg_fp.h',
          'third_party/dmg_fp/dtoa_wrapper.cc',
          'third_party/dmg_fp/g_fmt.cc',
          'third_party/icu/icu_utf.cc',
          'third_party/icu/icu_utf.h',
          'third_party/nspr/prtime.cc',
          'third_party/nspr/prtime.h',
          'thread_task_runner_handle.cc',
          'thread_task_runner_handle.h',
          'threading/non_thread_safe.h',
          'threading/non_thread_safe_impl.cc',
          'threading/non_thread_safe_impl.h',
          'threading/platform_thread.h',
          'threading/platform_thread_starboard.cc',
          'threading/post_task_and_reply_impl.cc',
          'threading/post_task_and_reply_impl.h',
          'threading/sequenced_worker_pool.cc',
          'threading/sequenced_worker_pool.h',
          'threading/simple_thread.cc',
          'threading/simple_thread.h',
          'threading/thread.cc',
          'threading/thread.h',
          'threading/thread_checker.h',
          'threading/thread_checker_impl.h',
          'threading/thread_checker_impl_atomic.cc',
          'threading/thread_collision_warner.cc',
          'threading/thread_collision_warner.h',
          'threading/thread_local.h',
          'threading/thread_local_starboard.cc',
          'threading/thread_local_storage.h',
          'threading/thread_local_storage_starboard.cc',
          'threading/thread_restrictions.cc',
          'threading/thread_restrictions.h',
          'threading/watchdog.cc',
          'threading/watchdog.h',
          'threading/worker_pool.cc',
          'threading/worker_pool.h',
          'threading/worker_pool_starboard.cc',
          'time.cc',
          'time.h',
          'time_starboard.cc',
          'timer.cc',
          'timer.h',
          'tracked_objects.cc',
          'tracked_objects.h',
          'tracking_info.cc',
          'tracking_info.h',
          'tuple.h',
          'utf_offset_string_conversions.cc',
          'utf_offset_string_conversions.h',
          'utf_string_conversion_utils.cc',
          'utf_string_conversion_utils.h',
          'utf_string_conversions.cc',
          'utf_string_conversions.h',
          'value_conversions.cc',
          'value_conversions.h',
          'values.cc',
          'values.h',
          'version.cc',
          'version.h',
          'vlog.cc',
          'vlog.h',
        ],
        'defines': [
          'BASE_IMPLEMENTATION',
        ],
        'include_dirs': [
          '<(DEPTH)',
        ],
      }],
    ],
  },
}
