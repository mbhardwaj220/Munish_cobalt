#version 100

precision mediump float;
uniform vec4 uTexDom_Stage1_c0;
uniform highp sampler2D uTextureSampler_0_Stage1;
varying mediump vec4 vcolor_Stage0;
varying highp vec2 vTransformedCoords_0_Stage0;
void main() {
    vec4 outputColor_Stage0;
    {
        outputColor_Stage0 = vcolor_Stage0;
    }
    vec4 output_Stage1;
    {
        vec4 child;
        {
            child = texture2D(uTextureSampler_0_Stage1, clamp(vTransformedCoords_0_Stage0, uTexDom_Stage1_c0.xy, uTexDom_Stage1_c0.zw));
        }
        output_Stage1 = child * outputColor_Stage0.w;
    }
    {
        gl_FragColor = output_Stage1;
    }
}
