# Copyright 2016 The Cobalt Authors. All Rights Reserved.
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

# This is a sample sandbox application for experimenting with the Cobalt
# render tree/renderer interface.

{
  'targets': [
    {
      'target_name': 'starboard_blitter_example',
      'type': '<(final_executable_type)',
      'sources': [
        'main.cc',
      ],
      'dependencies': [
        '<(DEPTH)/starboard/starboard.gyp:starboard',
      ],
    },
    {
      'target_name': 'starboard_blitter_example_deploy',
      'type': 'none',
      'dependencies': [
        'starboard_blitter_example',
      ],
      'variables': {
        'executable_name': 'starboard_blitter_example',
      },
      'includes': [ '<(DEPTH)/starboard/build/deploy.gypi' ],
    },
  ],
}
