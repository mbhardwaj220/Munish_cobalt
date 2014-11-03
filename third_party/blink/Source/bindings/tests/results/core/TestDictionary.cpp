// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py. DO NOT MODIFY!

#include "config.h"
#include "TestDictionary.h"


namespace blink {

TestDictionary::TestDictionary()
{
    setLongMember(1);
    setStringOrNullMember(String("default string value"));
    setEnumMember(String("foo"));
}

void TestDictionary::trace(Visitor* visitor)
{
    visitor->trace(m_testInterfaceGarbageCollectedMember);
    visitor->trace(m_testInterfaceGarbageCollectedOrNullMember);
    visitor->trace(m_testInterfaceWillBeGarbageCollectedMember);
    visitor->trace(m_testInterfaceWillBeGarbageCollectedOrNullMember);
    visitor->trace(m_elementOrNullMember);
}

} // namespace blink
