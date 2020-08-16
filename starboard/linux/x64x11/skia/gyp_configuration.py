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
"""Starboard Linux X64 X11 future platform configuration."""

from starboard.linux.x64x11 import gyp_configuration as linux_configuration


def CreatePlatformConfig():
  return linux_configuration.LinuxX64X11Configuration(
      'linux-x64x11-skia',
      sabi_json_path='starboard/sabi/x64/sysv/sabi-v{sb_api_version}.json')