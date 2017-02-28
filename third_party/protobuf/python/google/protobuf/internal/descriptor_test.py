#! /usr/bin/env python
#
# Protocol Buffers - Google's data interchange format
# Copyright 2008 Google Inc.  All rights reserved.
# https://developers.google.com/protocol-buffers/
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#     * Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above
# copyright notice, this list of conditions and the following disclaimer
# in the documentation and/or other materials provided with the
# distribution.
#     * Neither the name of Google Inc. nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

"""Unittest for google.protobuf.internal.descriptor."""

__author__ = 'robinson@google.com (Will Robinson)'

import sys

try:
  import unittest2 as unittest  #PY26
except ImportError:
  import unittest

from google.protobuf import unittest_custom_options_pb2
from google.protobuf import unittest_import_pb2
from google.protobuf import unittest_pb2
from google.protobuf import descriptor_pb2
from google.protobuf.internal import api_implementation
from google.protobuf.internal import test_util
from google.protobuf import descriptor
from google.protobuf import descriptor_pool
from google.protobuf import symbol_database
from google.protobuf import text_format


TEST_EMPTY_MESSAGE_DESCRIPTOR_ASCII = """
name: 'TestEmptyMessage'
"""


class DescriptorTest(unittest.TestCase):

  def setUp(self):
    file_proto = descriptor_pb2.FileDescriptorProto(
        name='some/filename/some.proto',
        package='protobuf_unittest')
    message_proto = file_proto.message_type.add(
        name='NestedMessage')
    message_proto.field.add(
        name='bb',
        number=1,
        type=descriptor_pb2.FieldDescriptorProto.TYPE_INT32,
        label=descriptor_pb2.FieldDescriptorProto.LABEL_OPTIONAL)
    enum_proto = message_proto.enum_type.add(
        name='ForeignEnum')
    enum_proto.value.add(name='FOREIGN_FOO', number=4)
    enum_proto.value.add(name='FOREIGN_BAR', number=5)
    enum_proto.value.add(name='FOREIGN_BAZ', number=6)

    self.pool = self.GetDescriptorPool()
    self.pool.Add(file_proto)
    self.my_file = self.pool.FindFileByName(file_proto.name)
    self.my_message = self.my_file.message_types_by_name[message_proto.name]
    self.my_enum = self.my_message.enum_types_by_name[enum_proto.name]

    self.my_method = descriptor.MethodDescriptor(
        name='Bar',
        full_name='protobuf_unittest.TestService.Bar',
        index=0,
        containing_service=None,
        input_type=None,
        output_type=None)
    self.my_service = descriptor.ServiceDescriptor(
        name='TestServiceWithOptions',
        full_name='protobuf_unittest.TestServiceWithOptions',
        file=self.my_file,
        index=0,
        methods=[
            self.my_method
        ])

  def GetDescriptorPool(self):
    return symbol_database.Default().pool

  def testEnumValueName(self):
    self.assertEqual(self.my_message.EnumValueName('ForeignEnum', 4),
                     'FOREIGN_FOO')

    self.assertEqual(
        self.my_message.enum_types_by_name[
            'ForeignEnum'].values_by_number[4].name,
        self.my_message.EnumValueName('ForeignEnum', 4))

  def testEnumFixups(self):
    self.assertEqual(self.my_enum, self.my_enum.values[0].type)

  def testContainingTypeFixups(self):
    self.assertEqual(self.my_message, self.my_message.fields[0].containing_type)
    self.assertEqual(self.my_message, self.my_enum.containing_type)

  def testContainingServiceFixups(self):
    self.assertEqual(self.my_service, self.my_method.containing_service)

  def testGetOptions(self):
    self.assertEqual(self.my_enum.GetOptions(),
                     descriptor_pb2.EnumOptions())
    self.assertEqual(self.my_enum.values[0].GetOptions(),
                     descriptor_pb2.EnumValueOptions())
    self.assertEqual(self.my_message.GetOptions(),
                     descriptor_pb2.MessageOptions())
    self.assertEqual(self.my_message.fields[0].GetOptions(),
                     descriptor_pb2.FieldOptions())
    self.assertEqual(self.my_method.GetOptions(),
                     descriptor_pb2.MethodOptions())
    self.assertEqual(self.my_service.GetOptions(),
                     descriptor_pb2.ServiceOptions())

  def testSimpleCustomOptions(self):
    file_descriptor = unittest_custom_options_pb2.DESCRIPTOR
    message_descriptor =\
        unittest_custom_options_pb2.TestMessageWithCustomOptions.DESCRIPTOR
    field_descriptor = message_descriptor.fields_by_name["field1"]
    enum_descriptor = message_descriptor.enum_types_by_name["AnEnum"]
    enum_value_descriptor =\
        message_descriptor.enum_values_by_name["ANENUM_VAL2"]
    service_descriptor =\
        unittest_custom_options_pb2.TestServiceWithCustomOptions.DESCRIPTOR
    method_descriptor = service_descriptor.FindMethodByName("Foo")

    file_options = file_descriptor.GetOptions()
    file_opt1 = unittest_custom_options_pb2.file_opt1
    self.assertEqual(9876543210, file_options.Extensions[file_opt1])
    message_options = message_descriptor.GetOptions()
    message_opt1 = unittest_custom_options_pb2.message_opt1
    self.assertEqual(-56, message_options.Extensions[message_opt1])
    field_options = field_descriptor.GetOptions()
    field_opt1 = unittest_custom_options_pb2.field_opt1
    self.assertEqual(8765432109, field_options.Extensions[field_opt1])
    field_opt2 = unittest_custom_options_pb2.field_opt2
    self.assertEqual(42, field_options.Extensions[field_opt2])
    enum_options = enum_descriptor.GetOptions()
    enum_opt1 = unittest_custom_options_pb2.enum_opt1
    self.assertEqual(-789, enum_options.Extensions[enum_opt1])
    enum_value_options = enum_value_descriptor.GetOptions()
    enum_value_opt1 = unittest_custom_options_pb2.enum_value_opt1
    self.assertEqual(123, enum_value_options.Extensions[enum_value_opt1])

    service_options = service_descriptor.GetOptions()
    service_opt1 = unittest_custom_options_pb2.service_opt1
    self.assertEqual(-9876543210, service_options.Extensions[service_opt1])
    method_options = method_descriptor.GetOptions()
    method_opt1 = unittest_custom_options_pb2.method_opt1
    self.assertEqual(unittest_custom_options_pb2.METHODOPT1_VAL2,
                     method_options.Extensions[method_opt1])

    message_descriptor = (
        unittest_custom_options_pb2.DummyMessageContainingEnum.DESCRIPTOR)
    self.assertTrue(file_descriptor.has_options)
    self.assertFalse(message_descriptor.has_options)

  def testDifferentCustomOptionTypes(self):
    kint32min = -2**31
    kint64min = -2**63
    kint32max = 2**31 - 1
    kint64max = 2**63 - 1
    kuint32max = 2**32 - 1
    kuint64max = 2**64 - 1

    message_descriptor =\
        unittest_custom_options_pb2.CustomOptionMinIntegerValues.DESCRIPTOR
    message_options = message_descriptor.GetOptions()
    self.assertEqual(False, message_options.Extensions[
        unittest_custom_options_pb2.bool_opt])
    self.assertEqual(kint32min, message_options.Extensions[
        unittest_custom_options_pb2.int32_opt])
    self.assertEqual(kint64min, message_options.Extensions[
        unittest_custom_options_pb2.int64_opt])
    self.assertEqual(0, message_options.Extensions[
        unittest_custom_options_pb2.uint32_opt])
    self.assertEqual(0, message_options.Extensions[
        unittest_custom_options_pb2.uint64_opt])
    self.assertEqual(kint32min, message_options.Extensions[
        unittest_custom_options_pb2.sint32_opt])
    self.assertEqual(kint64min, message_options.Extensions[
        unittest_custom_options_pb2.sint64_opt])
    self.assertEqual(0, message_options.Extensions[
        unittest_custom_options_pb2.fixed32_opt])
    self.assertEqual(0, message_options.Extensions[
        unittest_custom_options_pb2.fixed64_opt])
    self.assertEqual(kint32min, message_options.Extensions[
        unittest_custom_options_pb2.sfixed32_opt])
    self.assertEqual(kint64min, message_options.Extensions[
        unittest_custom_options_pb2.sfixed64_opt])

    message_descriptor =\
        unittest_custom_options_pb2.CustomOptionMaxIntegerValues.DESCRIPTOR
    message_options = message_descriptor.GetOptions()
    self.assertEqual(True, message_options.Extensions[
        unittest_custom_options_pb2.bool_opt])
    self.assertEqual(kint32max, message_options.Extensions[
        unittest_custom_options_pb2.int32_opt])
    self.assertEqual(kint64max, message_options.Extensions[
        unittest_custom_options_pb2.int64_opt])
    self.assertEqual(kuint32max, message_options.Extensions[
        unittest_custom_options_pb2.uint32_opt])
    self.assertEqual(kuint64max, message_options.Extensions[
        unittest_custom_options_pb2.uint64_opt])
    self.assertEqual(kint32max, message_options.Extensions[
        unittest_custom_options_pb2.sint32_opt])
    self.assertEqual(kint64max, message_options.Extensions[
        unittest_custom_options_pb2.sint64_opt])
    self.assertEqual(kuint32max, message_options.Extensions[
        unittest_custom_options_pb2.fixed32_opt])
    self.assertEqual(kuint64max, message_options.Extensions[
        unittest_custom_options_pb2.fixed64_opt])
    self.assertEqual(kint32max, message_options.Extensions[
        unittest_custom_options_pb2.sfixed32_opt])
    self.assertEqual(kint64max, message_options.Extensions[
        unittest_custom_options_pb2.sfixed64_opt])

    message_descriptor =\
        unittest_custom_options_pb2.CustomOptionOtherValues.DESCRIPTOR
    message_options = message_descriptor.GetOptions()
    self.assertEqual(-100, message_options.Extensions[
        unittest_custom_options_pb2.int32_opt])
    self.assertAlmostEqual(12.3456789, message_options.Extensions[
        unittest_custom_options_pb2.float_opt], 6)
    self.assertAlmostEqual(1.234567890123456789, message_options.Extensions[
        unittest_custom_options_pb2.double_opt])
    self.assertEqual("Hello, \"World\"", message_options.Extensions[
        unittest_custom_options_pb2.string_opt])
    self.assertEqual(b"Hello\0World", message_options.Extensions[
        unittest_custom_options_pb2.bytes_opt])
    dummy_enum = unittest_custom_options_pb2.DummyMessageContainingEnum
    self.assertEqual(
        dummy_enum.TEST_OPTION_ENUM_TYPE2,
        message_options.Extensions[unittest_custom_options_pb2.enum_opt])

    message_descriptor =\
        unittest_custom_options_pb2.SettingRealsFromPositiveInts.DESCRIPTOR
    message_options = message_descriptor.GetOptions()
    self.assertAlmostEqual(12, message_options.Extensions[
        unittest_custom_options_pb2.float_opt], 6)
    self.assertAlmostEqual(154, message_options.Extensions[
        unittest_custom_options_pb2.double_opt])

    message_descriptor =\
        unittest_custom_options_pb2.SettingRealsFromNegativeInts.DESCRIPTOR
    message_options = message_descriptor.GetOptions()
    self.assertAlmostEqual(-12, message_options.Extensions[
        unittest_custom_options_pb2.float_opt], 6)
    self.assertAlmostEqual(-154, message_options.Extensions[
        unittest_custom_options_pb2.double_opt])

  def testComplexExtensionOptions(self):
    descriptor =\
        unittest_custom_options_pb2.VariousComplexOptions.DESCRIPTOR
    options = descriptor.GetOptions()
    self.assertEqual(42, options.Extensions[
        unittest_custom_options_pb2.complex_opt1].foo)
    self.assertEqual(324, options.Extensions[
        unittest_custom_options_pb2.complex_opt1].Extensions[
            unittest_custom_options_pb2.quux])
    self.assertEqual(876, options.Extensions[
        unittest_custom_options_pb2.complex_opt1].Extensions[
            unittest_custom_options_pb2.corge].qux)
    self.assertEqual(987, options.Extensions[
        unittest_custom_options_pb2.complex_opt2].baz)
    self.assertEqual(654, options.Extensions[
        unittest_custom_options_pb2.complex_opt2].Extensions[
            unittest_custom_options_pb2.grault])
    self.assertEqual(743, options.Extensions[
        unittest_custom_options_pb2.complex_opt2].bar.foo)
    self.assertEqual(1999, options.Extensions[
        unittest_custom_options_pb2.complex_opt2].bar.Extensions[
            unittest_custom_options_pb2.quux])
    self.assertEqual(2008, options.Extensions[
        unittest_custom_options_pb2.complex_opt2].bar.Extensions[
            unittest_custom_options_pb2.corge].qux)
    self.assertEqual(741, options.Extensions[
        unittest_custom_options_pb2.complex_opt2].Extensions[
            unittest_custom_options_pb2.garply].foo)
    self.assertEqual(1998, options.Extensions[
        unittest_custom_options_pb2.complex_opt2].Extensions[
            unittest_custom_options_pb2.garply].Extensions[
                unittest_custom_options_pb2.quux])
    self.assertEqual(2121, options.Extensions[
        unittest_custom_options_pb2.complex_opt2].Extensions[
            unittest_custom_options_pb2.garply].Extensions[
                unittest_custom_options_pb2.corge].qux)
    self.assertEqual(1971, options.Extensions[
        unittest_custom_options_pb2.ComplexOptionType2
        .ComplexOptionType4.complex_opt4].waldo)
    self.assertEqual(321, options.Extensions[
        unittest_custom_options_pb2.complex_opt2].fred.waldo)
    self.assertEqual(9, options.Extensions[
        unittest_custom_options_pb2.complex_opt3].qux)
    self.assertEqual(22, options.Extensions[
        unittest_custom_options_pb2.complex_opt3].complexoptiontype5.plugh)
    self.assertEqual(24, options.Extensions[
        unittest_custom_options_pb2.complexopt6].xyzzy)

  # Check that aggregate options were parsed and saved correctly in
  # the appropriate descriptors.
  def testAggregateOptions(self):
    file_descriptor = unittest_custom_options_pb2.DESCRIPTOR
    message_descriptor =\
        unittest_custom_options_pb2.AggregateMessage.DESCRIPTOR
    field_descriptor = message_descriptor.fields_by_name["fieldname"]
    enum_descriptor = unittest_custom_options_pb2.AggregateEnum.DESCRIPTOR
    enum_value_descriptor = enum_descriptor.values_by_name["VALUE"]
    service_descriptor =\
        unittest_custom_options_pb2.AggregateService.DESCRIPTOR
    method_descriptor = service_descriptor.FindMethodByName("Method")

    # Tests for the different types of data embedded in fileopt
    file_options = file_descriptor.GetOptions().Extensions[
        unittest_custom_options_pb2.fileopt]
    self.assertEqual(100, file_options.i)
    self.assertEqual("FileAnnotation", file_options.s)
    self.assertEqual("NestedFileAnnotation", file_options.sub.s)
    self.assertEqual("FileExtensionAnnotation", file_options.file.Extensions[
        unittest_custom_options_pb2.fileopt].s)
    self.assertEqual("EmbeddedMessageSetElement", file_options.mset.Extensions[
        unittest_custom_options_pb2.AggregateMessageSetElement
        .message_set_extension].s)

    # Simple tests for all the other types of annotations
    self.assertEqual(
        "MessageAnnotation",
        message_descriptor.GetOptions().Extensions[
            unittest_custom_options_pb2.msgopt].s)
    self.assertEqual(
        "FieldAnnotation",
        field_descriptor.GetOptions().Extensions[
            unittest_custom_options_pb2.fieldopt].s)
    self.assertEqual(
        "EnumAnnotation",
        enum_descriptor.GetOptions().Extensions[
            unittest_custom_options_pb2.enumopt].s)
    self.assertEqual(
        "EnumValueAnnotation",
        enum_value_descriptor.GetOptions().Extensions[
            unittest_custom_options_pb2.enumvalopt].s)
    self.assertEqual(
        "ServiceAnnotation",
        service_descriptor.GetOptions().Extensions[
            unittest_custom_options_pb2.serviceopt].s)
    self.assertEqual(
        "MethodAnnotation",
        method_descriptor.GetOptions().Extensions[
            unittest_custom_options_pb2.methodopt].s)

  def testNestedOptions(self):
    nested_message =\
        unittest_custom_options_pb2.NestedOptionType.NestedMessage.DESCRIPTOR
    self.assertEqual(1001, nested_message.GetOptions().Extensions[
        unittest_custom_options_pb2.message_opt1])
    nested_field = nested_message.fields_by_name["nested_field"]
    self.assertEqual(1002, nested_field.GetOptions().Extensions[
        unittest_custom_options_pb2.field_opt1])
    outer_message =\
        unittest_custom_options_pb2.NestedOptionType.DESCRIPTOR
    nested_enum = outer_message.enum_types_by_name["NestedEnum"]
    self.assertEqual(1003, nested_enum.GetOptions().Extensions[
        unittest_custom_options_pb2.enum_opt1])
    nested_enum_value = outer_message.enum_values_by_name["NESTED_ENUM_VALUE"]
    self.assertEqual(1004, nested_enum_value.GetOptions().Extensions[
        unittest_custom_options_pb2.enum_value_opt1])
    nested_extension = outer_message.extensions_by_name["nested_extension"]
    self.assertEqual(1005, nested_extension.GetOptions().Extensions[
        unittest_custom_options_pb2.field_opt2])

  def testFileDescriptorReferences(self):
    self.assertEqual(self.my_enum.file, self.my_file)
    self.assertEqual(self.my_message.file, self.my_file)

  def testFileDescriptor(self):
    self.assertEqual(self.my_file.name, 'some/filename/some.proto')
    self.assertEqual(self.my_file.package, 'protobuf_unittest')
    self.assertEqual(self.my_file.pool, self.pool)
    # Generated modules also belong to the default pool.
    self.assertEqual(unittest_pb2.DESCRIPTOR.pool, descriptor_pool.Default())

  @unittest.skipIf(
      api_implementation.Type() != 'cpp' or api_implementation.Version() != 2,
      'Immutability of descriptors is only enforced in v2 implementation')
  def testImmutableCppDescriptor(self):
    message_descriptor = unittest_pb2.TestAllTypes.DESCRIPTOR
    with self.assertRaises(AttributeError):
      message_descriptor.fields_by_name = None
    with self.assertRaises(TypeError):
      message_descriptor.fields_by_name['Another'] = None
    with self.assertRaises(TypeError):
      message_descriptor.fields.append(None)


class NewDescriptorTest(DescriptorTest):
  """Redo the same tests as above, but with a separate DescriptorPool."""

  def GetDescriptorPool(self):
    return descriptor_pool.DescriptorPool()


class GeneratedDescriptorTest(unittest.TestCase):
  """Tests for the properties of descriptors in generated code."""

  def CheckMessageDescriptor(self, message_descriptor):
    # Basic properties
    self.assertEqual(message_descriptor.name, 'TestAllTypes')
    self.assertEqual(message_descriptor.full_name,
                     'protobuf_unittest.TestAllTypes')
    # Test equality and hashability
    self.assertEqual(message_descriptor, message_descriptor)
    self.assertEqual(message_descriptor.fields[0].containing_type,
                     message_descriptor)
    self.assertIn(message_descriptor, [message_descriptor])
    self.assertIn(message_descriptor, {message_descriptor: None})
    # Test field containers
    self.CheckDescriptorSequence(message_descriptor.fields)
    self.CheckDescriptorMapping(message_descriptor.fields_by_name)
    self.CheckDescriptorMapping(message_descriptor.fields_by_number)
    self.CheckDescriptorMapping(message_descriptor.fields_by_camelcase_name)

  def CheckFieldDescriptor(self, field_descriptor):
    # Basic properties
    self.assertEqual(field_descriptor.name, 'optional_int32')
    self.assertEqual(field_descriptor.camelcase_name, 'optionalInt32')
    self.assertEqual(field_descriptor.full_name,
                     'protobuf_unittest.TestAllTypes.optional_int32')
    self.assertEqual(field_descriptor.containing_type.name, 'TestAllTypes')
    # Test equality and hashability
    self.assertEqual(field_descriptor, field_descriptor)
    self.assertEqual(
        field_descriptor.containing_type.fields_by_name['optional_int32'],
        field_descriptor)
    self.assertEqual(
        field_descriptor.containing_type.fields_by_camelcase_name[
            'optionalInt32'],
        field_descriptor)
    self.assertIn(field_descriptor, [field_descriptor])
    self.assertIn(field_descriptor, {field_descriptor: None})

  def CheckDescriptorSequence(self, sequence):
    # Verifies that a property like 'messageDescriptor.fields' has all the
    # properties of an immutable abc.Sequence.
    self.assertGreater(len(sequence), 0)  # Sized
    self.assertEqual(len(sequence), len(list(sequence)))  # Iterable
    item = sequence[0]
    self.assertEqual(item, sequence[0])
    self.assertIn(item, sequence)  # Container
    self.assertEqual(sequence.index(item), 0)
    self.assertEqual(sequence.count(item), 1)
    reversed_iterator = reversed(sequence)
    self.assertEqual(list(reversed_iterator), list(sequence)[::-1])
    self.assertRaises(StopIteration, next, reversed_iterator)

  def CheckDescriptorMapping(self, mapping):
    # Verifies that a property like 'messageDescriptor.fields' has all the
    # properties of an immutable abc.Mapping.
    self.assertGreater(len(mapping), 0)  # Sized
    self.assertEqual(len(mapping), len(list(mapping)))  # Iterable
    if sys.version_info >= (3,):
      key, item = next(iter(mapping.items()))
    else:
      key, item = mapping.items()[0]
    self.assertIn(key, mapping)  # Container
    self.assertEqual(mapping.get(key), item)
    # keys(), iterkeys() &co
    item = (next(iter(mapping.keys())), next(iter(mapping.values())))
    self.assertEqual(item, next(iter(mapping.items())))
    if sys.version_info < (3,):
      def CheckItems(seq, iterator):
        self.assertEqual(next(iterator), seq[0])
        self.assertEqual(list(iterator), seq[1:])
      CheckItems(mapping.keys(), mapping.iterkeys())
      CheckItems(mapping.values(), mapping.itervalues())
      CheckItems(mapping.items(), mapping.iteritems())

  def testDescriptor(self):
    message_descriptor = unittest_pb2.TestAllTypes.DESCRIPTOR
    self.CheckMessageDescriptor(message_descriptor)
    field_descriptor = message_descriptor.fields_by_name['optional_int32']
    self.CheckFieldDescriptor(field_descriptor)
    field_descriptor = message_descriptor.fields_by_camelcase_name[
        'optionalInt32']
    self.CheckFieldDescriptor(field_descriptor)

  def testCppDescriptorContainer(self):
    # Check that the collection is still valid even if the parent disappeared.
    enum = unittest_pb2.TestAllTypes.DESCRIPTOR.enum_types_by_name['NestedEnum']
    values = enum.values
    del enum
    self.assertEqual('FOO', values[0].name)

  def testCppDescriptorContainer_Iterator(self):
    # Same test with the iterator
    enum = unittest_pb2.TestAllTypes.DESCRIPTOR.enum_types_by_name['NestedEnum']
    values_iter = iter(enum.values)
    del enum
    self.assertEqual('FOO', next(values_iter).name)


class DescriptorCopyToProtoTest(unittest.TestCase):
  """Tests for CopyTo functions of Descriptor."""

  def _AssertProtoEqual(self, actual_proto, expected_class, expected_ascii):
    expected_proto = expected_class()
    text_format.Merge(expected_ascii, expected_proto)

    self.assertEqual(
        actual_proto, expected_proto,
        'Not equal,\nActual:\n%s\nExpected:\n%s\n'
        % (str(actual_proto), str(expected_proto)))

  def _InternalTestCopyToProto(self, desc, expected_proto_class,
                               expected_proto_ascii):
    actual = expected_proto_class()
    desc.CopyToProto(actual)
    self._AssertProtoEqual(
        actual, expected_proto_class, expected_proto_ascii)

  def testCopyToProto_EmptyMessage(self):
    self._InternalTestCopyToProto(
        unittest_pb2.TestEmptyMessage.DESCRIPTOR,
        descriptor_pb2.DescriptorProto,
        TEST_EMPTY_MESSAGE_DESCRIPTOR_ASCII)

  def testCopyToProto_NestedMessage(self):
    TEST_NESTED_MESSAGE_ASCII = """
      name: 'NestedMessage'
      field: <
        name: 'bb'
        number: 1
        label: 1  # Optional
        type: 5  # TYPE_INT32
      >
      """

    self._InternalTestCopyToProto(
        unittest_pb2.TestAllTypes.NestedMessage.DESCRIPTOR,
        descriptor_pb2.DescriptorProto,
        TEST_NESTED_MESSAGE_ASCII)

  def testCopyToProto_ForeignNestedMessage(self):
    TEST_FOREIGN_NESTED_ASCII = """
      name: 'TestForeignNested'
      field: <
        name: 'foreign_nested'
        number: 1
        label: 1  # Optional
        type: 11  # TYPE_MESSAGE
        type_name: '.protobuf_unittest.TestAllTypes.NestedMessage'
      >
      """

    self._InternalTestCopyToProto(
        unittest_pb2.TestForeignNested.DESCRIPTOR,
        descriptor_pb2.DescriptorProto,
        TEST_FOREIGN_NESTED_ASCII)

  def testCopyToProto_ForeignEnum(self):
    TEST_FOREIGN_ENUM_ASCII = """
      name: 'ForeignEnum'
      value: <
        name: 'FOREIGN_FOO'
        number: 4
      >
      value: <
        name: 'FOREIGN_BAR'
        number: 5
      >
      value: <
        name: 'FOREIGN_BAZ'
        number: 6
      >
      """

    self._InternalTestCopyToProto(
        unittest_pb2.ForeignEnum.DESCRIPTOR,
        descriptor_pb2.EnumDescriptorProto,
        TEST_FOREIGN_ENUM_ASCII)

  def testCopyToProto_Options(self):
    TEST_DEPRECATED_FIELDS_ASCII = """
      name: 'TestDeprecatedFields'
      field: <
        name: 'deprecated_int32'
        number: 1
        label: 1  # Optional
        type: 5  # TYPE_INT32
        options: <
          deprecated: true
        >
      >
      """

    self._InternalTestCopyToProto(
        unittest_pb2.TestDeprecatedFields.DESCRIPTOR,
        descriptor_pb2.DescriptorProto,
        TEST_DEPRECATED_FIELDS_ASCII)

  def testCopyToProto_AllExtensions(self):
    TEST_EMPTY_MESSAGE_WITH_EXTENSIONS_ASCII = """
      name: 'TestEmptyMessageWithExtensions'
      extension_range: <
        start: 1
        end: 536870912
      >
      """

    self._InternalTestCopyToProto(
        unittest_pb2.TestEmptyMessageWithExtensions.DESCRIPTOR,
        descriptor_pb2.DescriptorProto,
        TEST_EMPTY_MESSAGE_WITH_EXTENSIONS_ASCII)

  def testCopyToProto_SeveralExtensions(self):
    TEST_MESSAGE_WITH_SEVERAL_EXTENSIONS_ASCII = """
      name: 'TestMultipleExtensionRanges'
      extension_range: <
        start: 42
        end: 43
      >
      extension_range: <
        start: 4143
        end: 4244
      >
      extension_range: <
        start: 65536
        end: 536870912
      >
      """

    self._InternalTestCopyToProto(
        unittest_pb2.TestMultipleExtensionRanges.DESCRIPTOR,
        descriptor_pb2.DescriptorProto,
        TEST_MESSAGE_WITH_SEVERAL_EXTENSIONS_ASCII)

  # Disable this test so we can make changes to the proto file.
  # TODO(xiaofeng): Enable this test after cl/55530659 is submitted.
  #
  # def testCopyToProto_FileDescriptor(self):
  #   UNITTEST_IMPORT_FILE_DESCRIPTOR_ASCII = ("""
  #     name: 'google/protobuf/unittest_import.proto'
  #     package: 'protobuf_unittest_import'
  #     dependency: 'google/protobuf/unittest_import_public.proto'
  #     message_type: <
  #       name: 'ImportMessage'
  #       field: <
  #         name: 'd'
  #         number: 1
  #         label: 1  # Optional
  #         type: 5  # TYPE_INT32
  #       >
  #     >
  #     """ +
  #     """enum_type: <
  #       name: 'ImportEnum'
  #       value: <
  #         name: 'IMPORT_FOO'
  #         number: 7
  #       >
  #       value: <
  #         name: 'IMPORT_BAR'
  #         number: 8
  #       >
  #       value: <
  #         name: 'IMPORT_BAZ'
  #         number: 9
  #       >
  #     >
  #     options: <
  #       java_package: 'com.google.protobuf.test'
  #       optimize_for: 1  # SPEED
  #     >
  #     public_dependency: 0
  #  """)
  #  self._InternalTestCopyToProto(
  #      unittest_import_pb2.DESCRIPTOR,
  #      descriptor_pb2.FileDescriptorProto,
  #      UNITTEST_IMPORT_FILE_DESCRIPTOR_ASCII)

  def testCopyToProto_ServiceDescriptor(self):
    TEST_SERVICE_ASCII = """
      name: 'TestService'
      method: <
        name: 'Foo'
        input_type: '.protobuf_unittest.FooRequest'
        output_type: '.protobuf_unittest.FooResponse'
      >
      method: <
        name: 'Bar'
        input_type: '.protobuf_unittest.BarRequest'
        output_type: '.protobuf_unittest.BarResponse'
      >
      """
    # TODO(rocking): enable this test after the proto descriptor change is
    # checked in.
    #self._InternalTestCopyToProto(
    #    unittest_pb2.TestService.DESCRIPTOR,
    #    descriptor_pb2.ServiceDescriptorProto,
    #    TEST_SERVICE_ASCII)


class MakeDescriptorTest(unittest.TestCase):

  def testMakeDescriptorWithNestedFields(self):
    file_descriptor_proto = descriptor_pb2.FileDescriptorProto()
    file_descriptor_proto.name = 'Foo2'
    message_type = file_descriptor_proto.message_type.add()
    message_type.name = file_descriptor_proto.name
    nested_type = message_type.nested_type.add()
    nested_type.name = 'Sub'
    enum_type = nested_type.enum_type.add()
    enum_type.name = 'FOO'
    enum_type_val = enum_type.value.add()
    enum_type_val.name = 'BAR'
    enum_type_val.number = 3
    field = message_type.field.add()
    field.number = 1
    field.name = 'uint64_field'
    field.label = descriptor.FieldDescriptor.LABEL_REQUIRED
    field.type = descriptor.FieldDescriptor.TYPE_UINT64
    field = message_type.field.add()
    field.number = 2
    field.name = 'nested_message_field'
    field.label = descriptor.FieldDescriptor.LABEL_REQUIRED
    field.type = descriptor.FieldDescriptor.TYPE_MESSAGE
    field.type_name = 'Sub'
    enum_field = nested_type.field.add()
    enum_field.number = 2
    enum_field.name = 'bar_field'
    enum_field.label = descriptor.FieldDescriptor.LABEL_REQUIRED
    enum_field.type = descriptor.FieldDescriptor.TYPE_ENUM
    enum_field.type_name = 'Foo2.Sub.FOO'

    result = descriptor.MakeDescriptor(message_type)
    self.assertEqual(result.fields[0].cpp_type,
                     descriptor.FieldDescriptor.CPPTYPE_UINT64)
    self.assertEqual(result.fields[1].cpp_type,
                     descriptor.FieldDescriptor.CPPTYPE_MESSAGE)
    self.assertEqual(result.fields[1].message_type.containing_type,
                     result)
    self.assertEqual(result.nested_types[0].fields[0].full_name,
                     'Foo2.Sub.bar_field')
    self.assertEqual(result.nested_types[0].fields[0].enum_type,
                     result.nested_types[0].enum_types[0])

  def testMakeDescriptorWithUnsignedIntField(self):
    file_descriptor_proto = descriptor_pb2.FileDescriptorProto()
    file_descriptor_proto.name = 'Foo'
    message_type = file_descriptor_proto.message_type.add()
    message_type.name = file_descriptor_proto.name
    enum_type = message_type.enum_type.add()
    enum_type.name = 'FOO'
    enum_type_val = enum_type.value.add()
    enum_type_val.name = 'BAR'
    enum_type_val.number = 3
    field = message_type.field.add()
    field.number = 1
    field.name = 'uint64_field'
    field.label = descriptor.FieldDescriptor.LABEL_REQUIRED
    field.type = descriptor.FieldDescriptor.TYPE_UINT64
    enum_field = message_type.field.add()
    enum_field.number = 2
    enum_field.name = 'bar_field'
    enum_field.label = descriptor.FieldDescriptor.LABEL_REQUIRED
    enum_field.type = descriptor.FieldDescriptor.TYPE_ENUM
    enum_field.type_name = 'Foo.FOO'

    result = descriptor.MakeDescriptor(message_type)
    self.assertEqual(result.fields[0].cpp_type,
                     descriptor.FieldDescriptor.CPPTYPE_UINT64)


  def testMakeDescriptorWithOptions(self):
    descriptor_proto = descriptor_pb2.DescriptorProto()
    aggregate_message = unittest_custom_options_pb2.AggregateMessage
    aggregate_message.DESCRIPTOR.CopyToProto(descriptor_proto)
    reformed_descriptor = descriptor.MakeDescriptor(descriptor_proto)

    options = reformed_descriptor.GetOptions()
    self.assertEqual(101,
                      options.Extensions[unittest_custom_options_pb2.msgopt].i)

  def testCamelcaseName(self):
    descriptor_proto = descriptor_pb2.DescriptorProto()
    descriptor_proto.name = 'Bar'
    names = ['foo_foo', 'FooBar', 'fooBaz', 'fooFoo', 'foobar']
    camelcase_names = ['fooFoo', 'fooBar', 'fooBaz', 'fooFoo', 'foobar']
    for index in range(len(names)):
      field = descriptor_proto.field.add()
      field.number = index + 1
      field.name = names[index]
    result = descriptor.MakeDescriptor(descriptor_proto)
    for index in range(len(camelcase_names)):
      self.assertEqual(result.fields[index].camelcase_name,
                       camelcase_names[index])


if __name__ == '__main__':
  unittest.main()
