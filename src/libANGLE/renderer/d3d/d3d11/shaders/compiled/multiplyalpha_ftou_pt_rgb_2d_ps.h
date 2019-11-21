#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//
//   fxc /nologo /E PS_FtoU_PT_RGB_2D /T ps_4_0 /Fh
//    compiled\multiplyalpha_ftou_pt_rgb_2d_ps.h MultiplyAlpha.hlsl
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// Sampler                           sampler      NA          NA    0        1
// TextureF                          texture  float4          2d    0        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_POSITION              0   xyzw        0      POS  float
// TEXCOORD                 0   xy          1     NONE  float   xy
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_TARGET                0   xyzw        0   TARGET   uint   xyzw
//
ps_4_0
dcl_sampler s0, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_input_ps linear v1.xy
dcl_output o0.xyzw
dcl_temps 1
sample r0.xyzw, v1.xyxx, t0.xyzw, s0
mul r0.xyz, r0.xyzx, l(255.000000, 255.000000, 255.000000, 0.000000)
ftou o0.xyz, r0.xyzx
mov o0.w, l(1)
ret
// Approximately 5 instruction slots used
#endif

const BYTE g_PS_FtoU_PT_RGB_2D[] = {
    68,  88,  66,  67,  239, 19,  57,  191, 36,  138, 64,  19,  35,  8,   170, 114, 160, 146, 147,
    152, 1,   0,   0,   0,   168, 2,   0,   0,   5,   0,   0,   0,   52,  0,   0,   0,   220, 0,
    0,   0,   52,  1,   0,   0,   104, 1,   0,   0,   44,  2,   0,   0,   82,  68,  69,  70,  160,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   0,   0,   0,   28,  0,   0,   0,
    0,   4,   255, 255, 0,   1,   0,   0,   109, 0,   0,   0,   92,  0,   0,   0,   3,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,
    0,   0,   1,   0,   0,   0,   100, 0,   0,   0,   2,   0,   0,   0,   5,   0,   0,   0,   4,
    0,   0,   0,   255, 255, 255, 255, 0,   0,   0,   0,   1,   0,   0,   0,   13,  0,   0,   0,
    83,  97,  109, 112, 108, 101, 114, 0,   84,  101, 120, 116, 117, 114, 101, 70,  0,   77,  105,
    99,  114, 111, 115, 111, 102, 116, 32,  40,  82,  41,  32,  72,  76,  83,  76,  32,  83,  104,
    97,  100, 101, 114, 32,  67,  111, 109, 112, 105, 108, 101, 114, 32,  57,  46,  50,  57,  46,
    57,  53,  50,  46,  51,  49,  49,  49,  0,   171, 171, 73,  83,  71,  78,  80,  0,   0,   0,
    2,   0,   0,   0,   8,   0,   0,   0,   56,  0,   0,   0,   0,   0,   0,   0,   1,   0,   0,
    0,   3,   0,   0,   0,   0,   0,   0,   0,   15,  0,   0,   0,   68,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   3,   0,   0,   0,   1,   0,   0,   0,   3,   3,   0,   0,   83,
    86,  95,  80,  79,  83,  73,  84,  73,  79,  78,  0,   84,  69,  88,  67,  79,  79,  82,  68,
    0,   171, 171, 171, 79,  83,  71,  78,  44,  0,   0,   0,   1,   0,   0,   0,   8,   0,   0,
    0,   32,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,
    0,   0,   15,  0,   0,   0,   83,  86,  95,  84,  65,  82,  71,  69,  84,  0,   171, 171, 83,
    72,  68,  82,  188, 0,   0,   0,   64,  0,   0,   0,   47,  0,   0,   0,   90,  0,   0,   3,
    0,   96,  16,  0,   0,   0,   0,   0,   88,  24,  0,   4,   0,   112, 16,  0,   0,   0,   0,
    0,   85,  85,  0,   0,   98,  16,  0,   3,   50,  16,  16,  0,   1,   0,   0,   0,   101, 0,
    0,   3,   242, 32,  16,  0,   0,   0,   0,   0,   104, 0,   0,   2,   1,   0,   0,   0,   69,
    0,   0,   9,   242, 0,   16,  0,   0,   0,   0,   0,   70,  16,  16,  0,   1,   0,   0,   0,
    70,  126, 16,  0,   0,   0,   0,   0,   0,   96,  16,  0,   0,   0,   0,   0,   56,  0,   0,
    10,  114, 0,   16,  0,   0,   0,   0,   0,   70,  2,   16,  0,   0,   0,   0,   0,   2,   64,
    0,   0,   0,   0,   127, 67,  0,   0,   127, 67,  0,   0,   127, 67,  0,   0,   0,   0,   28,
    0,   0,   5,   114, 32,  16,  0,   0,   0,   0,   0,   70,  2,   16,  0,   0,   0,   0,   0,
    54,  0,   0,   5,   130, 32,  16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   1,   0,   0,
    0,   62,  0,   0,   1,   83,  84,  65,  84,  116, 0,   0,   0,   5,   0,   0,   0,   1,   0,
    0,   0,   0,   0,   0,   0,   2,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,
    0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0};
