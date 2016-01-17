#version 100
precision mediump float;
uniform sampler2D uSampler0_Stage0;
uniform vec4 uTexDom_Stage0;
varying vec4 vColor;
varying vec2 vMatrixCoord_Stage0;
void main() {
  vec4 output_Stage0;
  {
    // Stage 0: TextureDomain
    output_Stage0 = (vColor * texture2D(
        uSampler0_Stage0,
        clamp(vMatrixCoord_Stage0, uTexDom_Stage0.xy, uTexDom_Stage0.zw)));
  }
  gl_FragColor = output_Stage0;
}
