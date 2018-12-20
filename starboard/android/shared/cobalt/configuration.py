# Copyright 2017 The Cobalt Authors. All Rights Reserved.
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
"""Starboard Android Cobalt shared configuration."""

import os

from cobalt.build import cobalt_configuration
from starboard.tools.testing import test_filter


class CobaltAndroidConfiguration(cobalt_configuration.CobaltConfiguration):
  """Starboard Android Cobalt shared configuration."""

  def __init__(self, platform_configuration, application_name,
               application_directory):
    super(CobaltAndroidConfiguration, self).__init__(
        platform_configuration, application_name, application_directory)

  def GetPostIncludes(self):
    # If there isn't a configuration.gypi found in the usual place, we'll
    # supplement with our shared implementation.
    includes = super(CobaltAndroidConfiguration, self).GetPostIncludes()
    for include in includes:
      if os.path.basename(include) == 'configuration.gypi':
        return includes

    shared_gypi_path = os.path.join(os.path.dirname(__file__),
                                    'configuration.gypi')
    if os.path.isfile(shared_gypi_path):
      includes.append(shared_gypi_path)
    return includes

  def WebdriverBenchmarksEnabled(self):
    return True

  def GetTestFilters(self):
    filters = super(CobaltAndroidConfiguration, self).GetTestFilters()
    for target, tests in self._FAILING_TESTS.iteritems():
      filters.extend(test_filter.TestFilter(target, test) for test in tests)
    return filters

  def GetTestEnvVariables(self):
    return {
        'base_unittests': {'ASAN_OPTIONS': 'detect_leaks=0'},
        'crypto_unittests': {'ASAN_OPTIONS': 'detect_leaks=0'},
        'net_unittests': {'ASAN_OPTIONS': 'detect_leaks=0'}
    }

  # A map of failing or crashing tests per target.
  _FAILING_TESTS = {
      'net_unittests': [
          'DialHttpServerTest.AllOtherRequests',
          'DialHttpServerTest.CallbackExceptionInServiceHandler',
          'DialHttpServerTest.CallbackHandleRequestReturnsFalse',
          'DialHttpServerTest.CallbackNormalTest',
          'DialHttpServerTest.CurrentRunningAppRedirect',
          'DialHttpServerTest.SendManifest',
          'HostResolverImplDnsTest.DnsTaskUnspec',
      ],
      'renderer_test': [
          'StressTest.TooManyTextures',
      ],
  }
