// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/test/test_suite.h"

int main(int argc, char** argv) {
  base::TestSuite test_suite(argc, argv);
  test_suite.EnforceTestIsolation();
  return test_suite.Run();
}
