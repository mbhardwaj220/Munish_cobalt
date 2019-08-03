#!/usr/bin/python
# Copyright 2016 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# gen_dxgi_format_table.py:
#  Code generation for DXGI format map.

from datetime import date
import sys

sys.path.append('../..')
import angle_format

template_cpp = """// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name} using data from {data_source_name}.
//
// Copyright {copyright_year} The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// DXGI format info:
//   Determining metadata about a DXGI format.

#include "libANGLE/renderer/Format.h"

using namespace angle;

namespace rx
{{

namespace d3d11
{{

GLenum GetComponentType(DXGI_FORMAT dxgiFormat)
{{
    switch (dxgiFormat)
    {{
{component_type_cases}        default:
            break;
    }}

    UNREACHABLE();
    return GL_NONE;
}}

}}  // namespace d3d11

namespace d3d11_angle
{{

const Format &GetFormat(DXGI_FORMAT dxgiFormat)
{{
    switch (dxgiFormat)
    {{
{format_cases}        default:
            break;
    }}

    UNREACHABLE();
    return Format::Get(Format::ID::NONE);
}}

}}  // namespace d3d11_angle

}}  // namespace rx
"""

template_format_case = """        case DXGI_FORMAT_{dxgi_format}:
            return {result};
"""

template_undefined_case = """        case DXGI_FORMAT_{dxgi_format}:
            break;
"""

def format_case(dxgi_format, result):
    return template_format_case.format(
        dxgi_format = dxgi_format,
        result = result)

def undefined_case(dxgi_format):
    return template_undefined_case.format(dxgi_format = dxgi_format)

component_cases = ""
format_cases = ""

input_data = 'dxgi_format_data.json'

dxgi_map = angle_format.load_json(input_data)

types = {
    'SNORM': 'GL_SIGNED_NORMALIZED',
    'UNORM': 'GL_UNSIGNED_NORMALIZED',
    'SINT': 'GL_INT',
    'UINT': 'GL_UNSIGNED_INT',
    'FLOAT': 'GL_FLOAT',
    'SHAREDEXP': 'GL_FLOAT'
}

angle_to_gl = angle_format.load_inverse_table('../../angle_format_map.json')
all_angle = angle_to_gl.keys()

for dxgi_format, angle_format in sorted(dxgi_map.iteritems()):

    found = [ctype in dxgi_format for ctype in types.keys()]
    count = reduce((lambda a, b: int(a) + int(b)), found)

    component_type = 'GL_NONE'

    if count == 1:
        gltype = next(gltype for ctype, gltype in types.iteritems() if ctype in dxgi_format)
        component_cases += format_case(dxgi_format, gltype)
    else:
        component_cases += undefined_case(dxgi_format)

    if angle_format == "":
        angle_format = dxgi_format

    if angle_format in all_angle:
        angle_format = "Format::Get(Format::ID::" + angle_format + ")"
        format_cases += format_case(dxgi_format, angle_format)
    else:
        format_cases += undefined_case(dxgi_format)

with open('dxgi_format_map_autogen.cpp', 'wt') as out_file:
    output_cpp = template_cpp.format(
        script_name = sys.argv[0],
        data_source_name = input_data,
        copyright_year = date.today().year,
        component_type_cases = component_cases,
        format_cases = format_cases)
    out_file.write(output_cpp)
    out_file.close()
