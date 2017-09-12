# Copyright 2015 Google Inc. All Rights Reserved.
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
      'target_name': 'examples',
      'type': 'none',
      'dependencies': [
        '<(DEPTH)/starboard/examples/blitter/blitter.gyp:starboard_blitter_example',
      ],
      'conditions': [
        ['not no_starboard_window_example', {
            '<(DEPTH)/starboard/examples/window/window.gyp:starboard_window_example',
          }
        ],
        ['gl_type != "none"', {
          'dependencies': [
            '<(DEPTH)/starboard/examples/glclear/glclear.gyp:starboard_glclear_example',
          ],
        }],
      ],
    },
  ],
}
