# Copyright 2019 The Cobalt Authors. All Rights Reserved.
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
      'target_name': 'video_dmp',
      'type': 'static_library',
      'sources': [
        '<(DEPTH)/starboard/shared/starboard/player/file_cache_reader.cc',
        '<(DEPTH)/starboard/shared/starboard/player/file_cache_reader.h',
        '<(DEPTH)/starboard/shared/starboard/player/video_dmp_common.cc',
        '<(DEPTH)/starboard/shared/starboard/player/video_dmp_common.h',
        '<(DEPTH)/starboard/shared/starboard/player/video_dmp_reader.cc',
        '<(DEPTH)/starboard/shared/starboard/player/video_dmp_reader.h',
      ],
      'dependencies': [
        '<(DEPTH)/starboard/starboard.gyp:starboard',
      ],
      'defines': [
        # This allows the tests to include internal only header files.
        'STARBOARD_IMPLEMENTATION',
      ],
    },
    {
      'target_name': 'player_copy_test_data',
      'type': 'none',
      'variables': {
        'content_test_input_files': ['<!@pymod_do_main(starboard.build.gyp_functions file_glob_sub <(DEPTH)/starboard/shared/starboard/player/testdata *.dmp.sha1 dmp.sha1 dmp)'],
        'content_test_output_subdir': 'starboard/shared/starboard/player/testdata',
        'download_from_google_storage_path': ['<!@pymod_do_main(starboard.build.gyp_functions find_program download_from_google_storage)'],
      },
      'actions' : [
        {
          # This action requires depot_tools to be in path
          # (https://cobalt.googlesource.com/depot_tools).
          'action_name': 'player_download_test_data',
          'action': [ '<(download_from_google_storage_path)',
                      '--no_resume',
                      '--no_auth',
                      '--num_threads', '8',
                      '--bucket', 'cobalt-static-storage',
                      '-d', '<(DEPTH)/starboard/shared/starboard/player/testdata',
          ],
          'inputs': [],
          'outputs': ['<!@pymod_do_main(starboard.build.gyp_functions file_glob_sub <(DEPTH)/starboard/shared/starboard/player/testdata *.dmp.sha1 dmp.sha1 dmp)'],
        },
      ],
      'includes': ['<(DEPTH)/starboard/build/copy_test_data.gypi'],
    },
  ],
}