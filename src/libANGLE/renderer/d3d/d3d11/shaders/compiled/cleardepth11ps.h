#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//
//   fxc /nologo /E PS_ClearDepth /T ps_4_0 /Fh compiled\cleardepth11ps.h
//    Clear11.hlsl
//
//
// Buffer Definitions: 
//
// cbuffer DepthOnlyData
// {
//
//   float zValue_Depth;                // Offset:   16 Size:     4
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// DepthOnlyData                     cbuffer      NA          NA    0        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_POSITION              0   xyzw        0      POS  float       
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_DEPTH                 0    N/A   oDepth    DEPTH  float    YES
//
ps_4_0
dcl_constantbuffer cb0[2], immediateIndexed
dcl_output oDepth
mov oDepth, cb0[1].x
ret 
// Approximately 2 instruction slots used
#endif

const BYTE g_PS_ClearDepth[] = {
    68,  88,  66,  67,  120, 231, 15,  116, 114, 21,  246, 235, 236, 14,  234, 123, 214, 247, 16,
    187, 1,   0,   0,   0,   48,  2,   0,   0,   5,   0,   0,   0,   52,  0,   0,   0,   12,  1,
    0,   0,   64,  1,   0,   0,   116, 1,   0,   0,   180, 1,   0,   0,   82,  68,  69,  70,  208,
    0,   0,   0,   1,   0,   0,   0,   76,  0,   0,   0,   1,   0,   0,   0,   28,  0,   0,   0,
    0,   4,   255, 255, 0,   1,   0,   0,   156, 0,   0,   0,   60,  0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,
    0,   0,   1,   0,   0,   0,   68,  101, 112, 116, 104, 79,  110, 108, 121, 68,  97,  116, 97,
    0,   171, 171, 60,  0,   0,   0,   1,   0,   0,   0,   100, 0,   0,   0,   32,  0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   124, 0,   0,   0,   16,  0,   0,   0,   4,   0,   0,
    0,   2,   0,   0,   0,   140, 0,   0,   0,   0,   0,   0,   0,   122, 86,  97,  108, 117, 101,
    95,  68,  101, 112, 116, 104, 0,   171, 171, 171, 0,   0,   3,   0,   1,   0,   1,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   77,  105, 99,  114, 111, 115, 111, 102, 116, 32,  40,  82,
    41,  32,  72,  76,  83,  76,  32,  83,  104, 97,  100, 101, 114, 32,  67,  111, 109, 112, 105,
    108, 101, 114, 32,  57,  46,  50,  57,  46,  57,  53,  50,  46,  51,  49,  49,  49,  0,   171,
    171, 171, 73,  83,  71,  78,  44,  0,   0,   0,   1,   0,   0,   0,   8,   0,   0,   0,   32,
    0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   3,   0,   0,   0,   0,   0,   0,   0,
    15,  0,   0,   0,   83,  86,  95,  80,  79,  83,  73,  84,  73,  79,  78,  0,   79,  83,  71,
    78,  44,  0,   0,   0,   1,   0,   0,   0,   8,   0,   0,   0,   32,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   3,   0,   0,   0,   255, 255, 255, 255, 1,   14,  0,   0,   83,
    86,  95,  68,  69,  80,  84,  72,  0,   171, 171, 171, 83,  72,  68,  82,  56,  0,   0,   0,
    64,  0,   0,   0,   14,  0,   0,   0,   89,  0,   0,   4,   70,  142, 32,  0,   0,   0,   0,
    0,   2,   0,   0,   0,   101, 0,   0,   2,   1,   192, 0,   0,   54,  0,   0,   5,   1,   192,
    0,   0,   10,  128, 32,  0,   0,   0,   0,   0,   1,   0,   0,   0,   62,  0,   0,   1,   83,
    84,  65,  84,  116, 0,   0,   0,   2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0};
