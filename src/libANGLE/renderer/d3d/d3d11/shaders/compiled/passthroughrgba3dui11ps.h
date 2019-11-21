#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//
//   fxc /nologo /E PS_PassthroughRGBA3DUI /T ps_4_0 /Fh
//    compiled\passthroughrgba3dui11ps.h Passthrough3D11.hlsl
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// TextureUI                         texture   uint4          3d    0        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_POSITION              0   xyzw        0      POS  float       
// SV_RENDERTARGETARRAYINDEX     0   x           1  RTINDEX   uint       
// TEXCOORD                 0   xyz         2     NONE  float   xyz 
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_TARGET                0   xyzw        0   TARGET   uint   xyzw
//
ps_4_0
dcl_resource_texture3d (uint,uint,uint,uint) t0
dcl_input_ps linear v2.xyz
dcl_output o0.xyzw
dcl_temps 1
resinfo_uint r0.xyzw, l(0), t0.xyzw
utof r0.xyz, r0.xyzx
mul r0.xyz, r0.xyzx, v2.xyzx
ftoi r0.xyz, r0.xyzx
mov r0.w, l(0)
ld o0.xyzw, r0.xyzw, t0.xyzw
ret 
// Approximately 7 instruction slots used
#endif

const BYTE g_PS_PassthroughRGBA3DUI[] = {
    68,  88,  66,  67,  117, 34,  123, 144, 139, 50,  107, 8,   199, 58,  188, 37, 26,  62,  108,
    21,  1,   0,   0,   0,   192, 2,   0,   0,   5,   0,   0,   0,   52,  0,   0,  0,   180, 0,
    0,   0,   60,  1,   0,   0,   112, 1,   0,   0,   68,  2,   0,   0,   82,  68, 69,  70,  120,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   28, 0,   0,   0,
    0,   4,   255, 255, 0,   1,   0,   0,   70,  0,   0,   0,   60,  0,   0,   0,  2,   0,   0,
    0,   4,   0,   0,   0,   8,   0,   0,   0,   255, 255, 255, 255, 0,   0,   0,  0,   1,   0,
    0,   0,   13,  0,   0,   0,   84,  101, 120, 116, 117, 114, 101, 85,  73,  0,  77,  105, 99,
    114, 111, 115, 111, 102, 116, 32,  40,  82,  41,  32,  72,  76,  83,  76,  32, 83,  104, 97,
    100, 101, 114, 32,  67,  111, 109, 112, 105, 108, 101, 114, 32,  57,  46,  50, 57,  46,  57,
    53,  50,  46,  51,  49,  49,  49,  0,   171, 73,  83,  71,  78,  128, 0,   0,  0,   3,   0,
    0,   0,   8,   0,   0,   0,   80,  0,   0,   0,   0,   0,   0,   0,   1,   0,  0,   0,   3,
    0,   0,   0,   0,   0,   0,   0,   15,  0,   0,   0,   92,  0,   0,   0,   0,  0,   0,   0,
    4,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,  118, 0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   0,   0,   0,   2,   0,   0,  0,   7,   7,
    0,   0,   83,  86,  95,  80,  79,  83,  73,  84,  73,  79,  78,  0,   83,  86, 95,  82,  69,
    78,  68,  69,  82,  84,  65,  82,  71,  69,  84,  65,  82,  82,  65,  89,  73, 78,  68,  69,
    88,  0,   84,  69,  88,  67,  79,  79,  82,  68,  0,   171, 79,  83,  71,  78, 44,  0,   0,
    0,   1,   0,   0,   0,   8,   0,   0,   0,   32,  0,   0,   0,   0,   0,   0,  0,   0,   0,
    0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   15,  0,   0,   0,   83,  86, 95,  84,  65,
    82,  71,  69,  84,  0,   171, 171, 83,  72,  68,  82,  204, 0,   0,   0,   64, 0,   0,   0,
    51,  0,   0,   0,   88,  40,  0,   4,   0,   112, 16,  0,   0,   0,   0,   0,  68,  68,  0,
    0,   98,  16,  0,   3,   114, 16,  16,  0,   2,   0,   0,   0,   101, 0,   0,  3,   242, 32,
    16,  0,   0,   0,   0,   0,   104, 0,   0,   2,   1,   0,   0,   0,   61,  16, 0,   7,   242,
    0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   70, 126, 16,  0,
    0,   0,   0,   0,   86,  0,   0,   5,   114, 0,   16,  0,   0,   0,   0,   0,  70,  2,   16,
    0,   0,   0,   0,   0,   56,  0,   0,   7,   114, 0,   16,  0,   0,   0,   0,  0,   70,  2,
    16,  0,   0,   0,   0,   0,   70,  18,  16,  0,   2,   0,   0,   0,   27,  0,  0,   5,   114,
    0,   16,  0,   0,   0,   0,   0,   70,  2,   16,  0,   0,   0,   0,   0,   54, 0,   0,   5,
    130, 0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,  45,  0,   0,
    7,   242, 32,  16,  0,   0,   0,   0,   0,   70,  14,  16,  0,   0,   0,   0,  0,   70,  126,
    16,  0,   0,   0,   0,   0,   62,  0,   0,   1,   83,  84,  65,  84,  116, 0,  0,   0,   7,
    0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   2,   0,   0,   0,   1,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,   0,   1,
    0,   0,   0,   0,   0,   0,   0,   2,   0,   0,   0,   0,   0,   0,   0,   0,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,   0,   0,
    0};
