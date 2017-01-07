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
"""Starboard Linux X64 X11 gcc 6.3 platform configuration for gyp_cobalt."""

import logging
import os
import subprocess
import sys

# Import the shared Linux platform configuration.
sys.path.append(
    os.path.realpath(
        os.path.join(
            os.path.dirname(__file__), os.pardir, os.pardir, os.pardir,
            'shared')))
import gyp_configuration as shared_configuration


class PlatformConfig(shared_configuration.PlatformConfig):
  """Starboard Linux platform configuration."""

  def __init__(self, platform, asan_enabled_by_default=False):
    super(PlatformConfig, self).__init__(platform, asan_enabled_by_default)

    # Run the script that ensures gcc 6.3.0 is installed.
    script_path = os.path.dirname(os.path.realpath(__file__))
    subprocess.call(
        os.path.join(script_path, 'download_gcc.sh'), cwd=script_path)
    script_path = os.path.dirname(os.path.realpath(__file__))
    base_path = os.path.realpath(
        os.path.join(script_path, '..', '..', '..', '..', '..'))
    self.toolchain = os.path.join(base_path, 'out', 'gcc-6.3.0', 'gcc')

  def GetVariables(self, configuration):
    variables = super(PlatformConfig, self).GetVariables(configuration)
    variables.update({'clang': 0,})
    toolchain_lib_path = os.path.join(self.toolchain, 'lib64')
    variables.update({'toolchain_lib_path': toolchain_lib_path,})
    return variables

  def GetEnvironmentVariables(self):
    env_variables = super(PlatformConfig, self).GetEnvironmentVariables()
    toolchain_bin_dir = os.path.join(self.toolchain, 'bin')
    env_variables.update({
        'CC': os.path.join(toolchain_bin_dir, 'gcc'),
        'CXX': os.path.join(toolchain_bin_dir, 'g++'),
    })
    return env_variables


def CreatePlatformConfig():
  try:
    return PlatformConfig('linux-x64x11-gcc-6-3')
  except RuntimeError as e:
    logging.critical(e)
    return None
