#!/usr/bin/python
# Copyright 2017 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# generate_gl_dispatch_table.py:
#  Generation script for OpenGL bindings with ANGLE.
#  NOTE: don't run this script directly. Run scripts/run_code_generation.py.

import sys
import os
import re
import xml.etree.ElementTree as etree
from datetime import date

# Set the CWD to the script directory.
os.chdir(os.path.dirname(os.path.abspath(sys.argv[0])))

sys.path.append('..')
import angle_format


def safe_append(the_dict, key, element):
    if key not in the_dict:
        the_dict[key] = []
    the_dict[key].append(element)


# Template for the header declaration of the dispatch table.
dispatch_table_header_template = """// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name} using data from {data_source_name} and gl.xml.
//
// Copyright {year} The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// {file_name}:
//   Defines the native binding interface for ANGLE's OpenGL back-end.

#ifndef LIBGLESV2_RENDERER_GL_DISPATCH_TABLE_GL_AUTOGEN_H_
#define LIBGLESV2_RENDERER_GL_DISPATCH_TABLE_GL_AUTOGEN_H_

#include "common/angleutils.h"
#include "libANGLE/renderer/gl/functionsgl_typedefs.h"

#include <set>

namespace gl
{{
struct Version;
}}  // namespace gl

namespace rx
{{
class DispatchTableGL : angle::NonCopyable
{{
  public:
  // clang-format off
{table_data}
  // clang-format on

  DispatchTableGL();
  virtual ~DispatchTableGL() = default;

  protected:
    virtual void *loadProcAddress(const std::string &function) const = 0;

    void initProcsDesktopGL(const gl::Version &version, const std::set<std::string> &extensions);
    void initProcsGLES(const gl::Version &version, const std::set<std::string> &extensions);
    void initProcsSharedExtensions(const std::set<std::string> &extensions);

#if defined(ANGLE_ENABLE_OPENGL_NULL)
    void initProcsDesktopGLNULL(const gl::Version &version, const std::set<std::string> &extensions);
    void initProcsGLESNULL(const gl::Version &version, const std::set<std::string> &extensions);
    void initProcsSharedExtensionsNULL(const std::set<std::string> &extensions);
#endif  // defined(ANGLE_ENABLE_OPENGL_NULL)
}};

}}  // namespace rx

#endif  // LIBGLESV2_RENDERER_GL_DISPATCH_TABLE_GL_AUTOGEN_H_
"""


def first_lower(str):
    return str[:1].lower() + str[1:]


def format_ep_decl(entry_point):
    return "    PFNGL" + entry_point.upper() + "PROC " + first_lower(entry_point) + " = nullptr;"


# Template for the initialization file of the dispatch table.
dispatch_table_source_template = """// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name} using data from {data_source_name} and gl.xml.
//
// Copyright {year} The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// {file_name}:
//   Initialize the native bindings for ANGLE's OpenGL back-end.

#include "libANGLE/renderer/gl/DispatchTableGL_autogen.h"

#include "libANGLE/Version.h"
#include "libANGLE/renderer/gl/FunctionsGL.h"

#if defined(ANGLE_ENABLE_OPENGL_NULL)
#include "libANGLE/renderer/gl/null_functions.h"
#endif  // defined(ANGLE_ENABLE_OPENGL_NULL)

// Check for nullptr so extensions do not overwrite core imports.
#define ASSIGN(NAME, FP) if (!FP) FP = reinterpret_cast<decltype(FP)>(loadProcAddress(NAME))

namespace rx
{{
DispatchTableGL::DispatchTableGL() = default;

void DispatchTableGL::initProcsDesktopGL(const gl::Version &version, const std::set<std::string> &extensions)
{{
{gl_data}

{gl_extensions_data}
}}

void DispatchTableGL::initProcsGLES(const gl::Version &version, const std::set<std::string> &extensions)
{{
{gles2_data}

{gles2_extensions_data}
}}

void DispatchTableGL::initProcsSharedExtensions(const std::set<std::string> &extensions)
{{
{both_extensions_data}
}}

#if defined(ANGLE_ENABLE_OPENGL_NULL)
void DispatchTableGL::initProcsDesktopGLNULL(const gl::Version &version, const std::set<std::string> &extensions)
{{
{gl_null_data}

{gl_null_extensions_data}
}}

void DispatchTableGL::initProcsGLESNULL(const gl::Version &version, const std::set<std::string> &extensions)
{{
{gles2_null_data}

{gles2_null_extensions_data}
}}

void DispatchTableGL::initProcsSharedExtensionsNULL(const std::set<std::string> &extensions)
{{
{both_null_extensions_data}
}}
#endif  // defined(ANGLE_ENABLE_OPENGL_NULL)

}}  // namespace rx
"""


def format_assign_ep(entry_point, ep):
    return '        ASSIGN("' + ep + '", ' + first_lower(entry_point[2:]) + ');'


def format_requirements_lines(required, entry_points):
    major, minor = required
    lines = ['    if (version >= gl::Version(' + major + ', ' + minor + '))', '    {']
    lines += [format_assign_ep(entry_point, entry_point) for entry_point in sorted(entry_points)]
    lines += ['    }']
    return '\n'.join(lines)


def format_extension_requirements_lines(extension, entry_points, api):
    lines = ['    if (extensions.count("' + extension + '") != 0)', '    {']
    lines += [format_assign_ep(entry_point, ep) for entry_point, ep in sorted(entry_points)]
    lines += ['    }']
    return '\n'.join(lines)


def assign_null_line(line):
    m = re.match(r'        ASSIGN\("gl.*", (.+)\);', line)
    if m:
        name = m.group(1)
        return '        ' + name + ' = &gl' + name[0].upper() + name[1:] + 'NULL;'
    else:
        return line


def assign_null(entry):
    return '\n'.join([assign_null_line(line) for line in entry.split('\n')])


def nullify(data):
    return [assign_null(entry) for entry in data]


def format_param(param):
    return "".join(param.itertext())


null_functions_header_template = """// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name} using data from {data_source_name} and gl.xml.
//
// Copyright {year} The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// {file_name}:
//   Declares the NULL/Stub bindings for the OpenGL back-end.

#ifndef LIBGLESV2_RENDERER_GL_NULL_GL_FUNCTIONS_AUTOGEN_H_
#define LIBGLESV2_RENDERER_GL_NULL_GL_FUNCTIONS_AUTOGEN_H_

#include "libANGLE/renderer/gl/functionsgl_typedefs.h"

namespace rx
{{
{table_data}
}}  // namespace rx

#endif  // LIBGLESV2_RENDERER_GL_NULL_GL_FUNCTIONS_AUTOGEN_H_
"""

null_functions_source_template = """// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name} using data from {data_source_name} and gl.xml.
//
// Copyright {year} The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// {file_name}:
//   Defines the NULL/Stub bindings for the OpenGL back-end.

#include "libANGLE/renderer/gl/null_functions.h"

namespace rx
{{
{table_data}
}}  // namespace rx
"""


def main():

    # auto_script parameters.
    if len(sys.argv) > 1:
        inputs = [
            '../../../../scripts/gl.xml',
            '../angle_format.py',
            'gl_bindings_data.json',
        ]
        outputs = [
            'DispatchTableGL_autogen.cpp',
            'DispatchTableGL_autogen.h',
            'null_functions.cpp',
            'null_functions.h',
        ]

        if sys.argv[1] == 'inputs':
            print ','.join(inputs)
        elif sys.argv[1] == 'outputs':
            print ','.join(outputs)
        else:
            print('Invalid script parameters')
            return 1
        return 0

    gl_xml_path = os.path.join('..', '..', '..', '..', 'scripts', 'gl.xml')
    dispatch_header_path = 'DispatchTableGL_autogen.h'
    dispatch_source_path = 'DispatchTableGL_autogen.cpp'
    null_functions_header_path = 'null_functions.h'
    null_functions_source_path = 'null_functions.cpp'

    # Load the JSON and XML data.
    data_source_name = 'gl_bindings_data.json'
    json_data = angle_format.load_json(data_source_name)
    xml_root = etree.parse(gl_xml_path).getroot()

    api_feature_info = {}

    core_removed_eps = []
    for core_removed_ep in xml_root.findall('feature/remove'):
        assert (core_removed_ep.attrib['profile'] == 'core')
        for command in core_removed_ep.findall('./command'):
            core_removed_eps.append(command.attrib['name'])

    for feature in xml_root.findall('feature'):
        api = feature.attrib['api']
        name = feature.attrib['name']
        number = feature.attrib['number']

        # OpenGL ES 3.x versions are listed as api 'gles2'
        if api != 'gl' and api != 'gles2':
            continue

        for command in feature.findall('./require/command'):
            command_name = command.attrib['name']
            safe_append(api_feature_info, command_name, (api, name, number))

    gl_extension_commands = {}
    gles2_extension_commands = {}
    both_extension_commands = {}

    for extension in xml_root.findall('extensions/extension'):
        extension_name = extension.attrib['name']
        support = extension.attrib['supported'].split('|')
        for command in extension.findall('./require/command'):
            command_name = command.attrib['name']
            if 'gl' in support and 'gles2' in support:
                # Special case for KHR extensions, since in GLES they are suffixed.
                if '_KHR_' in extension_name and not command_name.endswith('KHR'):
                    safe_append(gl_extension_commands, command_name, extension_name)
                    safe_append(gles2_extension_commands, command_name, extension_name)
                else:
                    safe_append(both_extension_commands, command_name, extension_name)
            elif 'gl' in support:
                safe_append(gl_extension_commands, command_name, extension_name)
            elif 'gles2' in support:
                safe_append(gles2_extension_commands, command_name, extension_name)

    gl_requirements = {}
    gles2_requirements = {}
    gl_extension_requirements = {}
    gles2_extension_requirements = {}
    both_extension_requirements = {}

    # Used later in the NULL bindings.
    all_entry_points = []

    for comment, entry_points in json_data.iteritems():
        for entry_point_no_prefix in entry_points:
            entry_point = "gl" + entry_point_no_prefix

            all_entry_points.append(entry_point)

            gl_required = None
            gles2_required = None

            if entry_point in api_feature_info:
                for api, name, number in api_feature_info[entry_point]:
                    major, minor = number.split(".")
                    reqs = (major, minor)
                    if api == 'gl':
                        if not gl_required:
                            gl_required = reqs
                        elif entry_point in core_removed_eps:
                            print('Upgrade ' + entry_point + ' to ' + str(reqs) + ' instead of ' +
                                  str(gl_required))
                            gl_required = reqs
                        else:
                            print('Keep ' + entry_point + ' at ' + str(gl_required) +
                                  ' instead of ' + str(reqs))
                    elif api == 'gles2':
                        if not gles2_required:
                            gles2_required = reqs
                        else:
                            print("Duplicate for " + entry_point + ": " + str(reqs) + " and " +
                                  str(gles2_required))
                    else:
                        raise Exception('Bad api type: ' + api)

            if gl_required:
                safe_append(gl_requirements, gl_required, entry_point)

            if gles2_required:
                safe_append(gles2_requirements, gles2_required, entry_point)

            # Special case for finding extensions that overlap with core functions.

            extension = False

            for ep in [entry_point, entry_point + "EXT", entry_point + "ARB", entry_point + "OES"]:
                if ep in both_extension_commands:
                    extension = True
                    for extension in both_extension_commands[ep]:
                        safe_append(both_extension_requirements, extension, (entry_point, ep))

                else:
                    if ep in gl_extension_commands:
                        extension = True
                        for extension in gl_extension_commands[ep]:
                            safe_append(gl_extension_requirements, extension, (entry_point, ep))

                    if ep in gles2_extension_commands:
                        extension = True
                        for extension in gles2_extension_commands[ep]:
                            full_ep = ep
                            if '_KHR_' in extension:
                                full_ep += 'KHR'
                            safe_append(gles2_extension_requirements, extension,
                                        (entry_point, full_ep))

            if not (gl_required or gles2_required or extension):
                raise Exception('Entry point ' + entry_point + ' not found in the xml.')

    table_data = []
    for comment, entry_points in sorted(json_data.iteritems()):
        formatted = ["    // " + comment]
        formatted += [format_ep_decl(entry_point) for entry_point in sorted(entry_points)]

        table_data.append("\n".join(formatted))

    dispatch_table_header = dispatch_table_header_template.format(
        script_name=os.path.basename(sys.argv[0]),
        data_source_name=data_source_name,
        year=date.today().year,
        file_name=dispatch_header_path,
        table_data="\n\n".join(table_data))

    with open(dispatch_header_path, "w") as out:
        out.write(dispatch_table_header)

    gl_data = []
    for gl_required, entry_points in sorted(gl_requirements.iteritems()):
        gl_data.append(format_requirements_lines(gl_required, entry_points))

    gl_extensions_data = []
    for extension, entry_points in sorted(gl_extension_requirements.iteritems()):
        gl_extensions_data.append(
            format_extension_requirements_lines(extension, entry_points, "gl"))

    gles2_data = []
    for gles2_required, entry_points in sorted(gles2_requirements.iteritems()):
        gles2_data.append(format_requirements_lines(gles2_required, entry_points))

    gles2_extensions_data = []
    for extension, entry_points in sorted(gles2_extension_requirements.iteritems()):
        gles2_extensions_data.append(
            format_extension_requirements_lines(extension, entry_points, "gles2"))

    both_extensions_data = []
    for extension, entry_points in sorted(both_extension_requirements.iteritems()):
        both_extensions_data.append(
            format_extension_requirements_lines(extension, entry_points, "gles2|gl"))

    dispatch_table_source = dispatch_table_source_template.format(
        script_name=os.path.basename(sys.argv[0]),
        data_source_name=data_source_name,
        year=date.today().year,
        file_name=dispatch_source_path,
        gl_data="\n\n".join(gl_data),
        gl_extensions_data="\n\n".join(gl_extensions_data),
        gles2_data="\n\n".join(gles2_data),
        gles2_extensions_data="\n\n".join(gles2_extensions_data),
        both_extensions_data="\n\n".join(both_extensions_data),
        gl_null_data="\n\n".join(nullify(gl_data)),
        gl_null_extensions_data="\n\n".join(nullify(gl_extensions_data)),
        gles2_null_data="\n\n".join(nullify(gles2_data)),
        gles2_null_extensions_data="\n\n".join(nullify(gles2_extensions_data)),
        both_null_extensions_data="\n\n".join(nullify(both_extensions_data)))

    with open(dispatch_source_path, "w") as out:
        out.write(dispatch_table_source)

    # Generate the NULL/stub entry points.
    # Process the whole set of commands

    command_defs = {}
    command_decls = {}

    for command in xml_root.findall('commands/command'):
        proto = command.find('proto')
        command_name = proto.find('name').text
        entry = ''.join(proto.itertext())
        return_type = entry[:-len(command_name)]
        entry = return_type + ' INTERNAL_GL_APIENTRY ' + entry[len(return_type):] + 'NULL('

        param_text = [format_param(param) for param in command.findall('param')]
        entry += ', '.join(param_text) + ')'

        command_decls[command_name] = entry + ';'

        entry += '\n{\n'
        if return_type != 'void ':
            entry += '    return static_cast<' + return_type + '>(0);\n'
        entry += '}'

        command_defs[command_name] = entry

    null_decls = [command_decls[entry_point] for entry_point in sorted(all_entry_points)]
    null_stubs = [command_defs[entry_point] for entry_point in sorted(all_entry_points)]

    null_functions_header = null_functions_header_template.format(
        script_name=os.path.basename(sys.argv[0]),
        data_source_name=data_source_name,
        year=date.today().year,
        file_name=null_functions_header_path,
        table_data="\n".join(null_decls))

    with open(null_functions_header_path, "w") as out:
        out.write(null_functions_header)

    null_functions_source = null_functions_source_template.format(
        script_name=os.path.basename(sys.argv[0]),
        data_source_name=data_source_name,
        year=date.today().year,
        file_name=null_functions_source_path,
        table_data="\n\n".join(null_stubs))

    with open(null_functions_source_path, "w") as out:
        out.write(null_functions_source)
    return 0


if __name__ == '__main__':
    sys.exit(main())
