#
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
#
"""Utility to prepend the top-level source directory to sys.path.

Since this may be used outside of gclient or git environment (such as part of a
tarball), the path to the root must be hardcoded.
"""

import os
import sys


def _GetSrcRoot():
  """Finds the first directory named 'src' that this module is in."""
  return os.path.abspath(os.path.join(__file__ ,os.pardir, os.pardir, os.pardir))

sys.path.insert(0, _GetSrcRoot())
