// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This webpage shows layout of YV12 and other YUV formats
// http://www.fourcc.org/yuv.php
// The actual conversion is best described here
// http://en.wikipedia.org/wiki/YUV
// excerpt from wiki:
//   These formulae are based on the NTSC standard;
//     Y' = 0.299 x R + 0.587 x G + 0.114 x B
//     U = -0.147 x R - 0.289 x G + 0.436 x B
//     V =  0.615 x R - 0.515 x G - 0.100 x B
//   On older, non-SIMD architectures, floating point arithmetic is much
//    slower than using fixed-point arithmetic, so an alternative formulation
//    is:
//      C = Y' - 16
//      D = U - 128
//      E = V - 128
//   Using the previous coefficients and noting that clip() denotes clipping a
//    value to the range of 0 to 255, the following formulae provide the
//    conversion from Y'UV to RGB (NTSC version):
//      R = clip((298 x C + 409 x E + 128) >> 8)
//      G = clip((298 x C - 100 x D - 208 x E + 128) >> 8)
//      B = clip((298 x C + 516 x D + 128) >> 8)
//
// An article on optimizing YUV conversion using tables instead of multiplies
//   http://lestourtereaux.free.fr/papers/data/yuvrgb.pdf
//
// Implimentation note
//   To improve performance, the 298 x C subexpression is 'hoisted'.
//   The shift by 8 is done on the subexpression, saving 2 shifts per pixel,
//   but introducing a half value error. (0.4% error)
//   ARGB pixel format is assumed, which on little endian is stored as BGRA.

#ifdef _OPENMP
#include <omp.h>
#endif

#include "base/logging.h"
#include "media/base/yuv_convert.h"

namespace media {

static const int kClipTableSize = 256;
static const int kClipOverflow = 128;

static uint8 g_rgb_clip_table[kClipOverflow
                            + kClipTableSize
                            + kClipOverflow] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 128 underflow values
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // clamped to 0.
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  // Unclipped values.
  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
  0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
  0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
  0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
  0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
  0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
  0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
  0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
  0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
  0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
  0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
  0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
  0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
  0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
  0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
  0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
  0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
  0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
  0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,
  0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
  0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7,
  0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
  0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7,
  0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
  0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7,
  0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
  0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7,
  0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
  0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7,
  0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // 128 overflow values
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // clamped to 255.
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

// Clip an rgb channel value to 0..255 range.
// Source is signed fixed point 8.8.
// Table allows for values to underflow or overflow by 128.
// Therefore source range is -128 to 384.
// Output clamps to unsigned 0 to 255.
static inline uint32 clip(int32 value) {
  DCHECK((((value) >> 8) + kClipOverflow) >= 0);
  DCHECK((((value) >> 8) + kClipOverflow)
         < kClipOverflow + kClipTableSize + kClipOverflow);
  return static_cast<uint32>(g_rgb_clip_table[((value) >> 8) + kClipOverflow]);
}

// Convert a frame of YUV to 32 bit ARGB.
void ConvertYV12ToRGB32(const uint8* yplane,
                        const uint8* uplane,
                        const uint8* vplane,
                        uint8* rgbframe,
                        size_t frame_width,
                        size_t frame_height,
                        int ystride,
                        int uvstride,
                        int rgbstride) {
  // Image must be multiple of 2 in both dimensions.
  DCHECK((frame_width & 1) == 0);
  DCHECK((frame_height & 1) == 0);
  // OpenMP note - Index in OpenMP must have signed integral type.
#ifdef _OPENMP
#pragma omp parallel for
#endif
  for (int32 y = 0; y < static_cast<int32>(frame_height); ++y) {
    const uint8* yrow = yplane + ystride  * y;
    const uint8* urow = uplane + uvstride * (y >> 1);
    const uint8* vrow = vplane + uvstride * (y >> 1);
    uint8* rgbrow  = rgbframe + rgbstride * y;

    for (int32 x = 0; x < static_cast<int32>(frame_width); x += 2) {
      uint8 u = urow[x >> 1];
      uint8 v = vrow[x >> 1];
      int32 D = static_cast<int32>(u) - 128;
      int32 E = static_cast<int32>(v) - 128;

      int32 Cb =   (516 * D + 128);
      int32 Cg = (- 100 * D - 208 * E + 128);
      int32 Cr =             (409 * E + 128);

      uint8 y0 = yrow[x];
      int32 C298a = ((static_cast<int32>(y0) - 16) * 298 + 128);
      *reinterpret_cast<uint32*>(rgbrow) = clip(C298a + Cb)
                                        | (clip(C298a + Cg) << 8)
                                        | (clip(C298a + Cr) << 16)
                                        | 0xff000000;

      uint8 y1 = yrow[x + 1];
      int32 C298b = ((static_cast<int32>(y1) - 16) * 298 + 128);
      *reinterpret_cast<uint32*>(rgbrow + 4) = clip(C298b + Cb)
                                            | (clip(C298b + Cg) << 8)
                                            | (clip(C298b + Cr) << 16)
                                            | 0xff000000;

      rgbrow += 8;  // Advance 2 pixels.
    }
  }
}

}  // namespace media

