#!/usr/bin/python2
#
# Copyright 2018 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# gen_blit11helper.py:
#   Generates the code for retrieving the various blit shaders for D3D11
#   NOTE: don't run this script directly. Run scripts/run_code_generation.py.

import sys, os, pprint
from datetime import date

template_blitshader_source = """// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name}.
//
// Copyright {year} The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Blit11Helper_autogen.inc:
//   Defines and retrieves blitshaders for the D3D11 backend.

namespace
{{
// Include inline shaders in the anonymous namespace to make sure no symbols are exported
{shader_includes}
}} // namespace

enum Blit11::BlitShaderOperation : unsigned int
{{
{blitshaderop_enums}
}};

enum Blit11::BlitShaderType : unsigned int
{{
{blitshadertype_enums}
}};

Blit11::BlitShaderType Blit11::getBlitShaderType(BlitShaderOperation operation, ShaderDimension dimension)
{{
    switch(operation)
    {{
{get_blitshaders_case_list}
        default:
            UNREACHABLE();
            return BLITSHADER_INVALID;
    }}
}}

angle::Result Blit11::mapBlitShader(const gl::Context *context,
                                    BlitShaderType blitShaderType)
{{
    switch(blitShaderType)
    {{
{add_blitshader_case_list}
        default:
            ANGLE_HR_UNREACHABLE(GetImplAs<Context11>(context));
    }}

    return angle::Result::Continue;
}}

"""

template_blitshaders_gni = """# GENERATED FILE - DO NOT EDIT.
# Generated by {script_name}.
#
# Copyright {year} The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# d3d11_blit_shaders_autogen.gni:
#   List of generated blit shaders for inclusion in ANGLE's build process.

libangle_d3d11_blit_shaders = [
{shader_filename_list}
]"""

template_compiled_blitshader_include = """#include "libANGLE/renderer/d3d/d3d11/shaders/compiled/{filename}\""""

template_get_blitshader_case = """        case {operation}:
            switch (dimension)
            {{
{get_blitshader_dimension_cases}
                default:
                    UNREACHABLE();
                    return BLITSHADER_INVALID;
            }}"""

template_get_blitshader_case_dimension = """                case SHADER_{dimension}:
                    return BLITSHADER_{blitshader};"""

template_map_blitshader_case = """        case {blitshader_name}:
            ANGLE_TRY(addBlitShaderToMap(context, blitShaderType, SHADER_{dimension_upper},
                                         ShaderData(g_PS_{compiled_shader_name}),
                                         "Blit11 {dimension} {shader_comment} pixel shader"));
            break;"""

supported_dimensions = ["2D", "3D", "2DArray"]

# field 1: BlitShaderType enum
# field 2: Name of compiled shader
# field 3: Filename of compiled shader
blitshader_data = [
    ("RGBAF", "PassthroughRGBA*", "passthroughrgba*11ps.h"), ("BGRAF", "PassthroughRGBA*"),
    ("RGBF", "PassthroughRGB*", "passthroughrgb*11ps.h"),
    ("RGF", "PassthroughRG*", "passthroughrg*11ps.h"),
    ("RF", "PassthroughR*", "passthroughr*11ps.h"),
    ("ALPHA", "PassthroughA*", "passthrougha*11ps.h"),
    ("LUMA", "PassthroughLum*", "passthroughlum*11ps.h"),
    ("LUMAALPHA", "PassthroughLumAlpha*", "passthroughlumalpha*11ps.h"),
    ("RGBAUI", "PassthroughRGBA*UI", "passthroughrgba*ui11ps.h"),
    ("RGBAI", "PassthroughRGBA*I", "passthroughrgba*i11ps.h"),
    ("RGBUI", "PassthroughRGB*UI", "passthroughrgb*ui11ps.h"),
    ("RGBI", "PassthroughRGB*I", "passthroughrgb*i11ps.h"),
    ("RGUI", "PassthroughRG*UI", "passthroughrg*ui11ps.h"),
    ("RGI", "PassthroughRG*I", "passthroughrg*i11ps.h"),
    ("RUI", "PassthroughR*UI", "passthroughr*ui11ps.h"),
    ("RI", "PassthroughR*I", "passthroughr*i11ps.h"),
    ("RGBAF_PREMULTIPLY", "FtoF_PM_RGBA_*", "multiplyalpha_ftof_pm_rgba_*_ps.h"),
    ("RGBAF_UNMULTIPLY", "FtoF_UM_RGBA_*", "multiplyalpha_ftof_um_rgba_*_ps.h"),
    ("RGBF_PREMULTIPLY", "FtoF_PM_RGB_*", "multiplyalpha_ftof_pm_rgb_*_ps.h"),
    ("RGBF_UNMULTIPLY", "FtoF_UM_RGB_*", "multiplyalpha_ftof_um_rgb_*_ps.h"),
    ("RGBAF_TOUI", "FtoU_PT_RGBA_*", "multiplyalpha_ftou_pt_rgba_*_ps.h"),
    ("RGBAF_TOUI_PREMULTIPLY", "FtoU_PM_RGBA_*", "multiplyalpha_ftou_pm_rgba_*_ps.h"),
    ("RGBAF_TOUI_UNMULTIPLY", "FtoU_UM_RGBA_*", "multiplyalpha_ftou_um_rgba_*_ps.h"),
    ("RGBF_TOUI", "FtoU_PT_RGB_*", "multiplyalpha_ftou_pt_rgb_*_ps.h"),
    ("RGBF_TOUI_PREMULTIPLY", "FtoU_PM_RGB_*", "multiplyalpha_ftou_pm_rgb_*_ps.h"),
    ("RGBF_TOUI_UNMULTIPLY", "FtoU_UM_RGB_*", "multiplyalpha_ftou_um_rgb_*_ps.h"),
    ("RGBAF_TOI", "FtoI_PT_RGBA_*", "multiplyalpha_ftoi_pt_rgba_*_ps.h"),
    ("RGBAF_TOI_PREMULTIPLY", "FtoI_PM_RGBA_*", "multiplyalpha_ftoi_pm_rgba_*_ps.h"),
    ("RGBAF_TOI_UNMULTIPLY", "FtoI_UM_RGBA_*", "multiplyalpha_ftoi_um_rgba_*_ps.h"),
    ("RGBF_TOI", "FtoI_PT_RGB_*", "multiplyalpha_ftoi_pt_rgb_*_ps.h"),
    ("RGBF_TOI_PREMULTIPLY", "FtoI_PM_RGB_*", "multiplyalpha_ftoi_pm_rgb_*_ps.h"),
    ("RGBF_TOI_UNMULTIPLY", "FtoI_UM_RGB_*", "multiplyalpha_ftoi_um_rgb_*_ps.h"),
    ("LUMAF_PREMULTIPLY", "FtoF_PM_LUMA_*", "multiplyalpha_ftof_pm_luma_*_ps.h"),
    ("LUMAF_UNMULTIPLY", "FtoF_UM_LUMA_*", "multiplyalpha_ftof_um_luma_*_ps.h"),
    ("LUMAALPHAF_PREMULTIPLY", "FtoF_PM_LUMAALPHA_*", "multiplyalpha_ftof_pm_lumaalpha_*_ps.h"),
    ("LUMAALPHAF_UNMULTIPLY", "FtoF_UM_LUMAALPHA_*", "multiplyalpha_ftof_um_lumaalpha_*_ps.h"),
    ("RGBAF_4444", "PassthroughRGBA*_4444", "passthroughrgba*_4444_11ps.h"),
    ("RGBAF_4444_PREMULTIPLY", "FtoF_PM_RGBA_4444_*", "multiplyalpha_ftof_pm_rgba_4444_*_ps.h"),
    ("RGBAF_4444_UNMULTIPLY", "FtoF_UM_RGBA_4444_*", "multiplyalpha_ftof_um_rgba_4444_*_ps.h"),
    ("RGBF_565", "PassthroughRGB*_565", "passthroughrgb*_565_11ps.h"),
    ("RGBF_565_PREMULTIPLY", "FtoF_PM_RGB_565_*", "multiplyalpha_ftof_pm_rgb_565_*_ps.h"),
    ("RGBF_565_UNMULTIPLY", "FtoF_UM_RGB_565_*", "multiplyalpha_ftof_um_rgb_565_*_ps.h"),
    ("RGBAF_5551", "PassthroughRGBA*_5551", "passthroughrgba*_5551_11ps.h"),
    ("RGBAF_5551_PREMULTIPLY", "FtoF_PM_RGBA_5551_*", "multiplyalpha_ftof_pm_rgba_5551_*_ps.h"),
    ("RGBAF_5551_UNMULTIPLY", "FtoF_UM_RGBA_5551_*", "multiplyalpha_ftof_um_rgba_5551_*_ps.h")
]


def format_shader_include(dimension, blitshader):
    return template_compiled_blitshader_include.format(
        filename=blitshader[2].replace("*", dimension.lower()))


def format_get_blitshader_case(operation):
    dimension_cases = []
    for dimension in supported_dimensions:
        dimension_cases.append(format_get_blitshader_case_dimension(operation, dimension))

    return template_get_blitshader_case.format(
        get_blitshader_dimension_cases="\n".join([c for c in dimension_cases]),
        operation=operation)


def format_get_blitshader_case_dimension(operation, dimension):
    # 2D float to int shaders have not been implemented
    if dimension == "2D" and operation.find("TOI") != -1:
        blitshader = "INVALID"
    else:
        blitshader = dimension.upper() + "_" + operation

    return template_get_blitshader_case_dimension.format(
        dimension=dimension.upper(), blitshader=blitshader)


def format_map_blitshader_case(dimension, blitshader):
    blitshader_name = "BLITSHADER_" + dimension.upper() + "_" + blitshader[0]

    # 3D and 2DArray use the RGBA shader for passthrough alpha
    if dimension != "2D" and blitshader[0] == "ALPHA":
        compiled_shader_name = "PassthroughRGBA" + dimension
    else:
        compiled_shader_name = blitshader[1].replace("*", dimension)

    shader_comment = compiled_shader_name.replace("_", " ")

    case = template_map_blitshader_case.format(
        blitshader_name=blitshader_name,
        dimension=dimension,
        dimension_upper=dimension.upper(),
        compiled_shader_name=compiled_shader_name,
        shader_comment=shader_comment,
    )

    return case


def format_shader_filename(dimension, blitshader):
    return "shaders/compiled/" + blitshader[2].replace("*", dimension.lower()) + ","


def get_shader_includes():
    includes = []

    for dimension in supported_dimensions:
        for blitshader in blitshader_data:
            # 2D float to int shaders have not been implemented
            if dimension == "2D" and blitshader[0].find("TOI") != -1:
                continue
            # 3D and 2DArray just use the RGBA shader for passthrough alpha
            if dimension != "2D" and blitshader[0] == "ALPHA":
                continue
            if len(blitshader) == 3:
                includes.append(format_shader_include(dimension, blitshader))

    return includes


def get_blitshader_cases():
    blitshader_cases = []
    for blitshader in blitshader_data:
        blitshader_cases.append(format_get_blitshader_case(blitshader[0]))

    return blitshader_cases


def get_map_blitshader_cases():
    blitshader_cases = []

    for dimension in supported_dimensions:
        for blitshader in blitshader_data:
            # 2D float to int shaders have not been implemented
            if dimension == "2D" and blitshader[0].find("TOI") != -1:
                continue
            blitshader_cases.append(format_map_blitshader_case(dimension, blitshader))

    return blitshader_cases


def get_blitshaderop_enums():
    blitshaderops = []

    for blitshader in blitshader_data:
        blitshaderops.append("    " + blitshader[0] + ",")

    blitshaderops.append("    OPERATION_INVALID")
    return blitshaderops


def get_blitshadertype_enums():
    blitshaders = []

    for dimension in supported_dimensions:
        for blitshader in blitshader_data:
            # 2D float to int shaders have not been implemented
            if dimension == "2D" and blitshader[0].find("TOI") != -1:
                continue
            blitshaders.append("    BLITSHADER_" + dimension.upper() + "_" + blitshader[0] + ",")

    blitshaders.append("    BLITSHADER_INVALID")
    return blitshaders


def get_shader_filenames():
    filenames = []

    for dimension in supported_dimensions:
        for blitshader in blitshader_data:
            # 2D float to int shaders have not been implemented
            if dimension == "2D" and blitshader[0].find("TOI") != -1:
                continue
            # 3D and 2DArray just use the RGBA shader for passthrough alpha
            if dimension != "2D" and blitshader[0] == "ALPHA":
                continue
            if len(blitshader) == 3:
                filenames.append(
                    ("    \"src/libANGLE/renderer/d3d/d3d11/shaders/compiled/{0}\",").format(
                        blitshader[2].replace("*", dimension.lower())))

    return filenames


def write_inc_file(get_blitshaders_case_list, add_blitshader_case_list, shader_includes,
                   blitshaderop_enums, blitshadertype_enums):
    content = template_blitshader_source.format(
        script_name=os.path.basename(sys.argv[0]),
        year=date.today().year,
        blitshaderop_enums=blitshaderop_enums,
        blitshadertype_enums=blitshadertype_enums,
        get_blitshaders_case_list=get_blitshaders_case_list,
        add_blitshader_case_list=add_blitshader_case_list,
        shader_includes=shader_includes)

    path = os.path.join("Blit11Helper_autogen.inc")

    with open(path, "w") as out:
        out.write(content)
        out.close()


def write_gni_file(shader_filename_list):
    content = template_blitshaders_gni.format(
        script_name=os.path.basename(sys.argv[0]),
        year=date.today().year,
        shader_filename_list=shader_filename_list)

    path = os.path.join("d3d11_blit_shaders_autogen.gni")

    with open(path, "w") as out:
        out.write(content)
        out.close()


def main():

    # auto_script parameters.
    if len(sys.argv) > 1:
        inputs = []
        outputs = ['Blit11Helper_autogen.inc', 'd3d11_blit_shaders_autogen.gni']

        if sys.argv[1] == 'inputs':
            print ','.join(inputs)
        elif sys.argv[1] == 'outputs':
            print ','.join(outputs)
        else:
            print('Invalid script parameters')
            return 1
        return 0

    map_blitshader_cases = []
    shader_includes = []
    blitshadertype_cases = []
    blitshadertype_enums = []
    blitshaderop_enums = []
    shader_filenames = []

    map_blitshader_cases = get_map_blitshader_cases()
    shader_includes = get_shader_includes()
    blitshadertype_cases = get_blitshader_cases()
    blitshaderop_enums = get_blitshaderop_enums()
    blitshadertype_enums = get_blitshadertype_enums()
    shader_filenames = get_shader_filenames()

    write_inc_file("\n".join([d for d in blitshadertype_cases]), "\n".join(
        [c for c in map_blitshader_cases]), "\n".join([i for i in shader_includes]), "\n".join(
            [e for e in blitshaderop_enums]), "\n".join([e for e in blitshadertype_enums]))
    write_gni_file("\n".join([s for s in shader_filenames]))
    return 0


if __name__ == '__main__':
    sys.exit(main())
