# Copyright 2017 Google Inc. All Rights Reserved.
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
"""Generate a conversion header for SpiderMonkey."""

import sys

import bootstrap_path  # pylint: disable=g-bad-import-order,unused-import

from cobalt.bindings.generate_conversion_header import generate_header
from cobalt.bindings.mozjs.code_generator_mozjs import CodeGeneratorMozjs

if __name__ == '__main__':
  sys.exit(generate_header(CodeGeneratorMozjs))
