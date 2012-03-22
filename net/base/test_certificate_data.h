// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

namespace {

// This is the SHA1 hash of the SubjectPublicKeyInfo of nist.der.
static const char nistSPKIHash[] =
    "\x15\x60\xde\x65\x4e\x03\x9f\xd0\x08\x82"
    "\xa9\x6a\xc4\x65\x8e\x6f\x92\x06\x84\x35";

// Certificates for test data. They're obtained with:
//
// $ openssl s_client -connect [host]:443 -showcerts > /tmp/host.pem < /dev/null
// $ openssl x509 -inform PEM -outform DER < /tmp/host.pem > /tmp/host.der
// $ xxd -i /tmp/host.der
//
// TODO(wtc): move these certificates to data files in the
// src/net/data/ssl/certificates directory.

// The linux compiler is nitty about unused variables.  Declaring variables
// in headers is not generally a good idea, but for our test data it is not
// a big deal.  Mark these as potentially unused so that the compiler won't
// complain.
#ifdef __GNUC__
#define VARIABLE_IS_NOT_USED __attribute__ ((unused))
#else
#define VARIABLE_IS_NOT_USED
#endif

// Google's cert.

unsigned char VARIABLE_IS_NOT_USED google_der[] = {
  0x30, 0x82, 0x03, 0x21, 0x30, 0x82, 0x02, 0x8a, 0xa0, 0x03, 0x02, 0x01,
  0x02, 0x02, 0x10, 0x01, 0x2a, 0x39, 0x76, 0x0d, 0x3f, 0x4f, 0xc9, 0x0b,
  0xe7, 0xbd, 0x2b, 0xcf, 0x95, 0x2e, 0x7a, 0x30, 0x0d, 0x06, 0x09, 0x2a,
  0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x05, 0x05, 0x00, 0x30, 0x4c,
  0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x5a,
  0x41, 0x31, 0x25, 0x30, 0x23, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x1c,
  0x54, 0x68, 0x61, 0x77, 0x74, 0x65, 0x20, 0x43, 0x6f, 0x6e, 0x73, 0x75,
  0x6c, 0x74, 0x69, 0x6e, 0x67, 0x20, 0x28, 0x50, 0x74, 0x79, 0x29, 0x20,
  0x4c, 0x74, 0x64, 0x2e, 0x31, 0x16, 0x30, 0x14, 0x06, 0x03, 0x55, 0x04,
  0x03, 0x13, 0x0d, 0x54, 0x68, 0x61, 0x77, 0x74, 0x65, 0x20, 0x53, 0x47,
  0x43, 0x20, 0x43, 0x41, 0x30, 0x1e, 0x17, 0x0d, 0x30, 0x39, 0x30, 0x33,
  0x32, 0x37, 0x32, 0x32, 0x32, 0x30, 0x30, 0x37, 0x5a, 0x17, 0x0d, 0x31,
  0x30, 0x30, 0x33, 0x32, 0x37, 0x32, 0x32, 0x32, 0x30, 0x30, 0x37, 0x5a,
  0x30, 0x68, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13,
  0x02, 0x55, 0x53, 0x31, 0x13, 0x30, 0x11, 0x06, 0x03, 0x55, 0x04, 0x08,
  0x13, 0x0a, 0x43, 0x61, 0x6c, 0x69, 0x66, 0x6f, 0x72, 0x6e, 0x69, 0x61,
  0x31, 0x16, 0x30, 0x14, 0x06, 0x03, 0x55, 0x04, 0x07, 0x13, 0x0d, 0x4d,
  0x6f, 0x75, 0x6e, 0x74, 0x61, 0x69, 0x6e, 0x20, 0x56, 0x69, 0x65, 0x77,
  0x31, 0x13, 0x30, 0x11, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x0a, 0x47,
  0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x20, 0x49, 0x6e, 0x63, 0x31, 0x17, 0x30,
  0x15, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x0e, 0x77, 0x77, 0x77, 0x2e,
  0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x30, 0x81,
  0x9f, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01,
  0x01, 0x01, 0x05, 0x00, 0x03, 0x81, 0x8d, 0x00, 0x30, 0x81, 0x89, 0x02,
  0x81, 0x81, 0x00, 0xd6, 0xb9, 0xe1, 0xad, 0xb8, 0x61, 0x0b, 0x1f, 0x4e,
  0xb6, 0x3c, 0x09, 0x3d, 0xab, 0xe8, 0xe3, 0x2b, 0xb6, 0xe8, 0xa4, 0x3a,
  0x78, 0x2f, 0xd3, 0x51, 0x20, 0x22, 0x45, 0x95, 0xd8, 0x00, 0x91, 0x33,
  0x9a, 0xa7, 0xa2, 0x48, 0xea, 0x30, 0x57, 0x26, 0x97, 0x66, 0xc7, 0x5a,
  0xef, 0xf1, 0x9b, 0x0c, 0x3f, 0xe1, 0xb9, 0x7f, 0x7b, 0xc3, 0xc7, 0xcc,
  0xaf, 0x9c, 0xd0, 0x1f, 0x3c, 0x81, 0x15, 0x10, 0x58, 0xfc, 0x06, 0xb3,
  0xbf, 0xbc, 0x9c, 0x02, 0xb9, 0x51, 0xdc, 0xfb, 0xa6, 0xb9, 0x17, 0x42,
  0xe6, 0x46, 0xe7, 0x22, 0xcf, 0x6c, 0x27, 0x10, 0xfe, 0x54, 0xe6, 0x92,
  0x6c, 0x0c, 0x60, 0x76, 0x9a, 0xce, 0xf8, 0x7f, 0xac, 0xb8, 0x5a, 0x08,
  0x4a, 0xdc, 0xb1, 0x64, 0xbd, 0xa0, 0x74, 0x41, 0xb2, 0xac, 0x8f, 0x86,
  0x9d, 0x1a, 0xde, 0x58, 0x09, 0xfd, 0x6c, 0x0a, 0x25, 0xe0, 0x79, 0x02,
  0x03, 0x01, 0x00, 0x01, 0xa3, 0x81, 0xe7, 0x30, 0x81, 0xe4, 0x30, 0x28,
  0x06, 0x03, 0x55, 0x1d, 0x25, 0x04, 0x21, 0x30, 0x1f, 0x06, 0x08, 0x2b,
  0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x01, 0x06, 0x08, 0x2b, 0x06, 0x01,
  0x05, 0x05, 0x07, 0x03, 0x02, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x86,
  0xf8, 0x42, 0x04, 0x01, 0x30, 0x36, 0x06, 0x03, 0x55, 0x1d, 0x1f, 0x04,
  0x2f, 0x30, 0x2d, 0x30, 0x2b, 0xa0, 0x29, 0xa0, 0x27, 0x86, 0x25, 0x68,
  0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x63, 0x72, 0x6c, 0x2e, 0x74, 0x68,
  0x61, 0x77, 0x74, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x54, 0x68, 0x61,
  0x77, 0x74, 0x65, 0x53, 0x47, 0x43, 0x43, 0x41, 0x2e, 0x63, 0x72, 0x6c,
  0x30, 0x72, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05, 0x05, 0x07, 0x01, 0x01,
  0x04, 0x66, 0x30, 0x64, 0x30, 0x22, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05,
  0x05, 0x07, 0x30, 0x01, 0x86, 0x16, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f,
  0x2f, 0x6f, 0x63, 0x73, 0x70, 0x2e, 0x74, 0x68, 0x61, 0x77, 0x74, 0x65,
  0x2e, 0x63, 0x6f, 0x6d, 0x30, 0x3e, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05,
  0x05, 0x07, 0x30, 0x02, 0x86, 0x32, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f,
  0x2f, 0x77, 0x77, 0x77, 0x2e, 0x74, 0x68, 0x61, 0x77, 0x74, 0x65, 0x2e,
  0x63, 0x6f, 0x6d, 0x2f, 0x72, 0x65, 0x70, 0x6f, 0x73, 0x69, 0x74, 0x6f,
  0x72, 0x79, 0x2f, 0x54, 0x68, 0x61, 0x77, 0x74, 0x65, 0x5f, 0x53, 0x47,
  0x43, 0x5f, 0x43, 0x41, 0x2e, 0x63, 0x72, 0x74, 0x30, 0x0c, 0x06, 0x03,
  0x55, 0x1d, 0x13, 0x01, 0x01, 0xff, 0x04, 0x02, 0x30, 0x00, 0x30, 0x0d,
  0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x05, 0x05,
  0x00, 0x03, 0x81, 0x81, 0x00, 0x39, 0xb6, 0xfb, 0x11, 0xbc, 0x33, 0x2c,
  0xc3, 0x90, 0x48, 0xe3, 0x6e, 0xc3, 0x9b, 0x38, 0xb1, 0x42, 0xd1, 0x00,
  0x09, 0x58, 0x63, 0xa0, 0xe1, 0x98, 0x1c, 0x85, 0xf2, 0xef, 0x10, 0x1d,
  0x60, 0x4e, 0x51, 0x09, 0x62, 0xf5, 0x05, 0xbd, 0x9d, 0x4f, 0x87, 0x6c,
  0x98, 0x72, 0x07, 0x80, 0xc3, 0x59, 0x48, 0x14, 0xe2, 0xd6, 0xef, 0xd0,
  0x8f, 0x33, 0x6a, 0x68, 0x31, 0xfa, 0xb7, 0xbb, 0x85, 0xcc, 0xf7, 0xc7,
  0x47, 0x7b, 0x67, 0x93, 0x3c, 0xc3, 0x16, 0x51, 0x9b, 0x6f, 0x87, 0x20,
  0xfd, 0x67, 0x4c, 0x2b, 0xea, 0x6a, 0x49, 0xdb, 0x11, 0xd1, 0xbd, 0xd7,
  0x95, 0x22, 0x43, 0x7a, 0x06, 0x7b, 0x4e, 0xf6, 0x37, 0x8e, 0xa2, 0xb9,
  0xcf, 0x1f, 0xa5, 0xd2, 0xbd, 0x3b, 0x04, 0x97, 0x39, 0xb3, 0x0f, 0xfa,
  0x38, 0xb5, 0xaf, 0x55, 0x20, 0x88, 0x60, 0x93, 0xf2, 0xde, 0xdb, 0xff,
  0xdf
};

// webkit.org's cert.

unsigned char VARIABLE_IS_NOT_USED webkit_der[] = {
  0x30, 0x82, 0x05, 0x0d, 0x30, 0x82, 0x03, 0xf5, 0xa0, 0x03, 0x02, 0x01,
  0x02, 0x02, 0x03, 0x43, 0xdd, 0x63, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86,
  0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x05, 0x05, 0x00, 0x30, 0x81, 0xca,
  0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x55,
  0x53, 0x31, 0x10, 0x30, 0x0e, 0x06, 0x03, 0x55, 0x04, 0x08, 0x13, 0x07,
  0x41, 0x72, 0x69, 0x7a, 0x6f, 0x6e, 0x61, 0x31, 0x13, 0x30, 0x11, 0x06,
  0x03, 0x55, 0x04, 0x07, 0x13, 0x0a, 0x53, 0x63, 0x6f, 0x74, 0x74, 0x73,
  0x64, 0x61, 0x6c, 0x65, 0x31, 0x1a, 0x30, 0x18, 0x06, 0x03, 0x55, 0x04,
  0x0a, 0x13, 0x11, 0x47, 0x6f, 0x44, 0x61, 0x64, 0x64, 0x79, 0x2e, 0x63,
  0x6f, 0x6d, 0x2c, 0x20, 0x49, 0x6e, 0x63, 0x2e, 0x31, 0x33, 0x30, 0x31,
  0x06, 0x03, 0x55, 0x04, 0x0b, 0x13, 0x2a, 0x68, 0x74, 0x74, 0x70, 0x3a,
  0x2f, 0x2f, 0x63, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74,
  0x65, 0x73, 0x2e, 0x67, 0x6f, 0x64, 0x61, 0x64, 0x64, 0x79, 0x2e, 0x63,
  0x6f, 0x6d, 0x2f, 0x72, 0x65, 0x70, 0x6f, 0x73, 0x69, 0x74, 0x6f, 0x72,
  0x79, 0x31, 0x30, 0x30, 0x2e, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x27,
  0x47, 0x6f, 0x20, 0x44, 0x61, 0x64, 0x64, 0x79, 0x20, 0x53, 0x65, 0x63,
  0x75, 0x72, 0x65, 0x20, 0x43, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69, 0x63,
  0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x41, 0x75, 0x74, 0x68, 0x6f, 0x72,
  0x69, 0x74, 0x79, 0x31, 0x11, 0x30, 0x0f, 0x06, 0x03, 0x55, 0x04, 0x05,
  0x13, 0x08, 0x30, 0x37, 0x39, 0x36, 0x39, 0x32, 0x38, 0x37, 0x30, 0x1e,
  0x17, 0x0d, 0x30, 0x38, 0x30, 0x33, 0x31, 0x38, 0x32, 0x33, 0x33, 0x35,
  0x31, 0x39, 0x5a, 0x17, 0x0d, 0x31, 0x31, 0x30, 0x33, 0x31, 0x38, 0x32,
  0x33, 0x33, 0x35, 0x31, 0x39, 0x5a, 0x30, 0x79, 0x31, 0x0b, 0x30, 0x09,
  0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x55, 0x53, 0x31, 0x13, 0x30,
  0x11, 0x06, 0x03, 0x55, 0x04, 0x08, 0x13, 0x0a, 0x43, 0x61, 0x6c, 0x69,
  0x66, 0x6f, 0x72, 0x6e, 0x69, 0x61, 0x31, 0x12, 0x30, 0x10, 0x06, 0x03,
  0x55, 0x04, 0x07, 0x13, 0x09, 0x43, 0x75, 0x70, 0x65, 0x72, 0x74, 0x69,
  0x6e, 0x6f, 0x31, 0x13, 0x30, 0x11, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13,
  0x0a, 0x41, 0x70, 0x70, 0x6c, 0x65, 0x20, 0x49, 0x6e, 0x63, 0x2e, 0x31,
  0x15, 0x30, 0x13, 0x06, 0x03, 0x55, 0x04, 0x0b, 0x13, 0x0c, 0x4d, 0x61,
  0x63, 0x20, 0x4f, 0x53, 0x20, 0x46, 0x6f, 0x72, 0x67, 0x65, 0x31, 0x15,
  0x30, 0x13, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x0c, 0x2a, 0x2e, 0x77,
  0x65, 0x62, 0x6b, 0x69, 0x74, 0x2e, 0x6f, 0x72, 0x67, 0x30, 0x81, 0x9f,
  0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01,
  0x01, 0x05, 0x00, 0x03, 0x81, 0x8d, 0x00, 0x30, 0x81, 0x89, 0x02, 0x81,
  0x81, 0x00, 0xa7, 0x62, 0x79, 0x41, 0xda, 0x28, 0xf2, 0xc0, 0x4f, 0xe0,
  0x25, 0xaa, 0xa1, 0x2e, 0x3b, 0x30, 0x94, 0xb5, 0xc9, 0x26, 0x3a, 0x1b,
  0xe2, 0xd0, 0xcc, 0xa2, 0x95, 0xe2, 0x91, 0xc0, 0xf0, 0x40, 0x9e, 0x27,
  0x6e, 0xbd, 0x6e, 0xde, 0x7c, 0xb6, 0x30, 0x5c, 0xb8, 0x9b, 0x01, 0x2f,
  0x92, 0x04, 0xa1, 0xef, 0x4a, 0xb1, 0x6c, 0xb1, 0x7e, 0x8e, 0xcd, 0xa6,
  0xf4, 0x40, 0x73, 0x1f, 0x2c, 0x96, 0xad, 0xff, 0x2a, 0x6d, 0x0e, 0xba,
  0x52, 0x84, 0x83, 0xb0, 0x39, 0xee, 0xc9, 0x39, 0xdc, 0x1e, 0x34, 0xd0,
  0xd8, 0x5d, 0x7a, 0x09, 0xac, 0xa9, 0xee, 0xca, 0x65, 0xf6, 0x85, 0x3a,
  0x6b, 0xee, 0xe4, 0x5c, 0x5e, 0xf8, 0xda, 0xd1, 0xce, 0x88, 0x47, 0xcd,
  0x06, 0x21, 0xe0, 0xb9, 0x4b, 0xe4, 0x07, 0xcb, 0x57, 0xdc, 0xca, 0x99,
  0x54, 0xf7, 0x0e, 0xd5, 0x17, 0x95, 0x05, 0x2e, 0xe9, 0xb1, 0x02, 0x03,
  0x01, 0x00, 0x01, 0xa3, 0x82, 0x01, 0xce, 0x30, 0x82, 0x01, 0xca, 0x30,
  0x09, 0x06, 0x03, 0x55, 0x1d, 0x13, 0x04, 0x02, 0x30, 0x00, 0x30, 0x0b,
  0x06, 0x03, 0x55, 0x1d, 0x0f, 0x04, 0x04, 0x03, 0x02, 0x05, 0xa0, 0x30,
  0x1d, 0x06, 0x03, 0x55, 0x1d, 0x25, 0x04, 0x16, 0x30, 0x14, 0x06, 0x08,
  0x2b, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x01, 0x06, 0x08, 0x2b, 0x06,
  0x01, 0x05, 0x05, 0x07, 0x03, 0x02, 0x30, 0x57, 0x06, 0x03, 0x55, 0x1d,
  0x1f, 0x04, 0x50, 0x30, 0x4e, 0x30, 0x4c, 0xa0, 0x4a, 0xa0, 0x48, 0x86,
  0x46, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x63, 0x65, 0x72, 0x74,
  0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x65, 0x73, 0x2e, 0x67, 0x6f, 0x64,
  0x61, 0x64, 0x64, 0x79, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x72, 0x65, 0x70,
  0x6f, 0x73, 0x69, 0x74, 0x6f, 0x72, 0x79, 0x2f, 0x67, 0x6f, 0x64, 0x61,
  0x64, 0x64, 0x79, 0x65, 0x78, 0x74, 0x65, 0x6e, 0x64, 0x65, 0x64, 0x69,
  0x73, 0x73, 0x75, 0x69, 0x6e, 0x67, 0x33, 0x2e, 0x63, 0x72, 0x6c, 0x30,
  0x52, 0x06, 0x03, 0x55, 0x1d, 0x20, 0x04, 0x4b, 0x30, 0x49, 0x30, 0x47,
  0x06, 0x0b, 0x60, 0x86, 0x48, 0x01, 0x86, 0xfd, 0x6d, 0x01, 0x07, 0x17,
  0x02, 0x30, 0x38, 0x30, 0x36, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05, 0x05,
  0x07, 0x02, 0x01, 0x16, 0x2a, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f,
  0x63, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x65, 0x73,
  0x2e, 0x67, 0x6f, 0x64, 0x61, 0x64, 0x64, 0x79, 0x2e, 0x63, 0x6f, 0x6d,
  0x2f, 0x72, 0x65, 0x70, 0x6f, 0x73, 0x69, 0x74, 0x6f, 0x72, 0x79, 0x30,
  0x7f, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05, 0x05, 0x07, 0x01, 0x01, 0x04,
  0x73, 0x30, 0x71, 0x30, 0x23, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05, 0x05,
  0x07, 0x30, 0x01, 0x86, 0x17, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f,
  0x6f, 0x63, 0x73, 0x70, 0x2e, 0x67, 0x6f, 0x64, 0x61, 0x64, 0x64, 0x79,
  0x2e, 0x63, 0x6f, 0x6d, 0x30, 0x4a, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05,
  0x05, 0x07, 0x30, 0x02, 0x86, 0x3e, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f,
  0x2f, 0x63, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x65,
  0x73, 0x2e, 0x67, 0x6f, 0x64, 0x61, 0x64, 0x64, 0x79, 0x2e, 0x63, 0x6f,
  0x6d, 0x2f, 0x72, 0x65, 0x70, 0x6f, 0x73, 0x69, 0x74, 0x6f, 0x72, 0x79,
  0x2f, 0x67, 0x64, 0x5f, 0x69, 0x6e, 0x74, 0x65, 0x72, 0x6d, 0x65, 0x64,
  0x69, 0x61, 0x74, 0x65, 0x2e, 0x63, 0x72, 0x74, 0x30, 0x1d, 0x06, 0x03,
  0x55, 0x1d, 0x0e, 0x04, 0x16, 0x04, 0x14, 0x48, 0xdf, 0x60, 0x32, 0xcc,
  0x89, 0x01, 0xb6, 0xdc, 0x2f, 0xe3, 0x73, 0xb5, 0x9c, 0x16, 0x58, 0x32,
  0x68, 0xa9, 0xc3, 0x30, 0x1f, 0x06, 0x03, 0x55, 0x1d, 0x23, 0x04, 0x18,
  0x30, 0x16, 0x80, 0x14, 0xfd, 0xac, 0x61, 0x32, 0x93, 0x6c, 0x45, 0xd6,
  0xe2, 0xee, 0x85, 0x5f, 0x9a, 0xba, 0xe7, 0x76, 0x99, 0x68, 0xcc, 0xe7,
  0x30, 0x23, 0x06, 0x03, 0x55, 0x1d, 0x11, 0x04, 0x1c, 0x30, 0x1a, 0x82,
  0x0c, 0x2a, 0x2e, 0x77, 0x65, 0x62, 0x6b, 0x69, 0x74, 0x2e, 0x6f, 0x72,
  0x67, 0x82, 0x0a, 0x77, 0x65, 0x62, 0x6b, 0x69, 0x74, 0x2e, 0x6f, 0x72,
  0x67, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01,
  0x01, 0x05, 0x05, 0x00, 0x03, 0x82, 0x01, 0x01, 0x00, 0x1e, 0x6a, 0xe7,
  0xe0, 0x4f, 0xe7, 0x4d, 0xd0, 0x69, 0x7c, 0xf8, 0x8f, 0x99, 0xb4, 0x18,
  0x95, 0x36, 0x24, 0x0f, 0x0e, 0xa3, 0xea, 0x34, 0x37, 0xf4, 0x7d, 0xd5,
  0x92, 0x35, 0x53, 0x72, 0x76, 0x3f, 0x69, 0xf0, 0x82, 0x56, 0xe3, 0x94,
  0x7a, 0x1d, 0x1a, 0x81, 0xaf, 0x9f, 0xc7, 0x43, 0x01, 0x64, 0xd3, 0x7c,
  0x0d, 0xc8, 0x11, 0x4e, 0x4a, 0xe6, 0x1a, 0xc3, 0x01, 0x74, 0xe8, 0x35,
  0x87, 0x5c, 0x61, 0xaa, 0x8a, 0x46, 0x06, 0xbe, 0x98, 0x95, 0x24, 0x9e,
  0x01, 0xe3, 0xe6, 0xa0, 0x98, 0xee, 0x36, 0x44, 0x56, 0x8d, 0x23, 0x9c,
  0x65, 0xea, 0x55, 0x6a, 0xdf, 0x66, 0xee, 0x45, 0xe8, 0xa0, 0xe9, 0x7d,
  0x9a, 0xba, 0x94, 0xc5, 0xc8, 0xc4, 0x4b, 0x98, 0xff, 0x9a, 0x01, 0x31,
  0x6d, 0xf9, 0x2b, 0x58, 0xe7, 0xe7, 0x2a, 0xc5, 0x4d, 0xbb, 0xbb, 0xcd,
  0x0d, 0x70, 0xe1, 0xad, 0x03, 0xf5, 0xfe, 0xf4, 0x84, 0x71, 0x08, 0xd2,
  0xbc, 0x04, 0x7b, 0x26, 0x1c, 0xa8, 0x0f, 0x9c, 0xd8, 0x12, 0x6a, 0x6f,
  0x2b, 0x67, 0xa1, 0x03, 0x80, 0x9a, 0x11, 0x0b, 0xe9, 0xe0, 0xb5, 0xb3,
  0xb8, 0x19, 0x4e, 0x0c, 0xa4, 0xd9, 0x2b, 0x3b, 0xc2, 0xca, 0x20, 0xd3,
  0x0c, 0xa4, 0xff, 0x93, 0x13, 0x1f, 0xfc, 0xba, 0x94, 0x93, 0x8c, 0x64,
  0x15, 0x2e, 0x28, 0xa9, 0x55, 0x8c, 0x2c, 0x48, 0xd3, 0xd3, 0xc1, 0x50,
  0x69, 0x19, 0xe8, 0x34, 0xd3, 0xf1, 0x04, 0x9f, 0x0a, 0x7a, 0x21, 0x87,
  0xbf, 0xb9, 0x59, 0x37, 0x2e, 0xf4, 0x71, 0xa5, 0x3e, 0xbe, 0xcd, 0x70,
  0x83, 0x18, 0xf8, 0x8a, 0x72, 0x85, 0x45, 0x1f, 0x08, 0x01, 0x6f, 0x37,
  0xf5, 0x2b, 0x7b, 0xea, 0xb9, 0x8b, 0xa3, 0xcc, 0xfd, 0x35, 0x52, 0xdd,
  0x66, 0xde, 0x4f, 0x30, 0xc5, 0x73, 0x81, 0xb6, 0xe8, 0x3c, 0xd8, 0x48,
  0x8a
};

// thawte.com's cert (it's EV-licious!).
unsigned char VARIABLE_IS_NOT_USED thawte_der[] = {
  0x30, 0x82, 0x04, 0xa5, 0x30, 0x82, 0x03, 0x8d, 0xa0, 0x03, 0x02, 0x01,
  0x02, 0x02, 0x10, 0x17, 0x76, 0x05, 0x88, 0x95, 0x58, 0xee, 0xbb, 0x00,
  0xda, 0x10, 0xe5, 0xf0, 0xf3, 0x9c, 0xf0, 0x30, 0x0d, 0x06, 0x09, 0x2a,
  0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x05, 0x05, 0x00, 0x30, 0x81,
  0x8b, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02,
  0x55, 0x53, 0x31, 0x15, 0x30, 0x13, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13,
  0x0c, 0x74, 0x68, 0x61, 0x77, 0x74, 0x65, 0x2c, 0x20, 0x49, 0x6e, 0x63,
  0x2e, 0x31, 0x39, 0x30, 0x37, 0x06, 0x03, 0x55, 0x04, 0x0b, 0x13, 0x30,
  0x54, 0x65, 0x72, 0x6d, 0x73, 0x20, 0x6f, 0x66, 0x20, 0x75, 0x73, 0x65,
  0x20, 0x61, 0x74, 0x20, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f,
  0x77, 0x77, 0x77, 0x2e, 0x74, 0x68, 0x61, 0x77, 0x74, 0x65, 0x2e, 0x63,
  0x6f, 0x6d, 0x2f, 0x63, 0x70, 0x73, 0x20, 0x28, 0x63, 0x29, 0x30, 0x36,
  0x31, 0x2a, 0x30, 0x28, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x21, 0x74,
  0x68, 0x61, 0x77, 0x74, 0x65, 0x20, 0x45, 0x78, 0x74, 0x65, 0x6e, 0x64,
  0x65, 0x64, 0x20, 0x56, 0x61, 0x6c, 0x69, 0x64, 0x61, 0x74, 0x69, 0x6f,
  0x6e, 0x20, 0x53, 0x53, 0x4c, 0x20, 0x43, 0x41, 0x30, 0x1e, 0x17, 0x0d,
  0x30, 0x38, 0x31, 0x31, 0x31, 0x39, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
  0x5a, 0x17, 0x0d, 0x31, 0x30, 0x30, 0x31, 0x31, 0x37, 0x32, 0x33, 0x35,
  0x39, 0x35, 0x39, 0x5a, 0x30, 0x81, 0xc7, 0x31, 0x13, 0x30, 0x11, 0x06,
  0x0b, 0x2b, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x3c, 0x02, 0x01, 0x03,
  0x13, 0x02, 0x55, 0x53, 0x31, 0x19, 0x30, 0x17, 0x06, 0x0b, 0x2b, 0x06,
  0x01, 0x04, 0x01, 0x82, 0x37, 0x3c, 0x02, 0x01, 0x02, 0x14, 0x08, 0x44,
  0x65, 0x6c, 0x61, 0x77, 0x61, 0x72, 0x65, 0x31, 0x1b, 0x30, 0x19, 0x06,
  0x03, 0x55, 0x04, 0x0f, 0x13, 0x12, 0x56, 0x31, 0x2e, 0x30, 0x2c, 0x20,
  0x43, 0x6c, 0x61, 0x75, 0x73, 0x65, 0x20, 0x35, 0x2e, 0x28, 0x62, 0x29,
  0x31, 0x13, 0x30, 0x11, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x14, 0x0a, 0x54,
  0x68, 0x61, 0x77, 0x74, 0x65, 0x20, 0x49, 0x6e, 0x63, 0x31, 0x10, 0x30,
  0x0e, 0x06, 0x03, 0x55, 0x04, 0x05, 0x13, 0x07, 0x33, 0x38, 0x39, 0x38,
  0x32, 0x36, 0x31, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06,
  0x13, 0x02, 0x55, 0x53, 0x31, 0x13, 0x30, 0x11, 0x06, 0x03, 0x55, 0x04,
  0x08, 0x13, 0x0a, 0x43, 0x61, 0x6c, 0x69, 0x66, 0x6f, 0x72, 0x6e, 0x69,
  0x61, 0x31, 0x16, 0x30, 0x14, 0x06, 0x03, 0x55, 0x04, 0x07, 0x14, 0x0d,
  0x4d, 0x6f, 0x75, 0x6e, 0x74, 0x61, 0x69, 0x6e, 0x20, 0x56, 0x69, 0x65,
  0x77, 0x31, 0x17, 0x30, 0x15, 0x06, 0x03, 0x55, 0x04, 0x03, 0x14, 0x0e,
  0x77, 0x77, 0x77, 0x2e, 0x74, 0x68, 0x61, 0x77, 0x74, 0x65, 0x2e, 0x63,
  0x6f, 0x6d, 0x30, 0x81, 0x9f, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48,
  0x86, 0xf7, 0x0d, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x81, 0x8d, 0x00,
  0x30, 0x81, 0x89, 0x02, 0x81, 0x81, 0x00, 0xe7, 0x89, 0x68, 0xb5, 0x6e,
  0x1d, 0x38, 0x19, 0xf6, 0x2d, 0x61, 0xc2, 0x00, 0xba, 0x6e, 0xab, 0x66,
  0x92, 0xd6, 0x85, 0x87, 0x2d, 0xd5, 0xa8, 0x58, 0xa9, 0x7a, 0x75, 0x27,
  0x9d, 0xed, 0x9e, 0xfe, 0x06, 0x71, 0x70, 0x2d, 0x21, 0x70, 0x4c, 0x3e,
  0x9c, 0xb6, 0xd5, 0x5d, 0x44, 0x92, 0xb4, 0xe0, 0xee, 0x7c, 0x0a, 0x50,
  0x4c, 0x0d, 0x67, 0x98, 0xaa, 0x01, 0x0e, 0x37, 0xa3, 0x2a, 0xef, 0xe6,
  0xe0, 0x11, 0x7b, 0xee, 0xb0, 0xa2, 0xb4, 0x32, 0x64, 0xa7, 0x0d, 0xda,
  0x6c, 0x15, 0xf8, 0xc5, 0xa5, 0x5a, 0x2c, 0xfc, 0xc9, 0xa6, 0x3c, 0x88,
  0x88, 0xbf, 0xdf, 0xa7, 0x38, 0xf0, 0x78, 0xed, 0x81, 0x93, 0x29, 0x0c,
  0xae, 0xc7, 0xab, 0x51, 0x21, 0x5e, 0xca, 0x95, 0xe5, 0x48, 0x52, 0x41,
  0xb6, 0x18, 0x60, 0x04, 0x19, 0x6f, 0x3d, 0x80, 0x14, 0xd3, 0xaf, 0x23,
  0x03, 0x10, 0x95, 0x02, 0x03, 0x01, 0x00, 0x01, 0xa3, 0x82, 0x01, 0x49,
  0x30, 0x82, 0x01, 0x45, 0x30, 0x0c, 0x06, 0x03, 0x55, 0x1d, 0x13, 0x01,
  0x01, 0xff, 0x04, 0x02, 0x30, 0x00, 0x30, 0x39, 0x06, 0x03, 0x55, 0x1d,
  0x1f, 0x04, 0x32, 0x30, 0x30, 0x30, 0x2e, 0xa0, 0x2c, 0xa0, 0x2a, 0x86,
  0x28, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x63, 0x72, 0x6c, 0x2e,
  0x74, 0x68, 0x61, 0x77, 0x74, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x54,
  0x68, 0x61, 0x77, 0x74, 0x65, 0x45, 0x56, 0x43, 0x41, 0x32, 0x30, 0x30,
  0x36, 0x2e, 0x63, 0x72, 0x6c, 0x30, 0x42, 0x06, 0x03, 0x55, 0x1d, 0x20,
  0x04, 0x3b, 0x30, 0x39, 0x30, 0x37, 0x06, 0x0b, 0x60, 0x86, 0x48, 0x01,
  0x86, 0xf8, 0x45, 0x01, 0x07, 0x30, 0x01, 0x30, 0x28, 0x30, 0x26, 0x06,
  0x08, 0x2b, 0x06, 0x01, 0x05, 0x05, 0x07, 0x02, 0x01, 0x16, 0x1a, 0x68,
  0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x74,
  0x68, 0x61, 0x77, 0x74, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x63, 0x70,
  0x73, 0x30, 0x1d, 0x06, 0x03, 0x55, 0x1d, 0x25, 0x04, 0x16, 0x30, 0x14,
  0x06, 0x08, 0x2b, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x01, 0x06, 0x08,
  0x2b, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x02, 0x30, 0x1f, 0x06, 0x03,
  0x55, 0x1d, 0x23, 0x04, 0x18, 0x30, 0x16, 0x80, 0x14, 0xcd, 0x32, 0xe2,
  0xf2, 0x5d, 0x25, 0x47, 0x02, 0xaa, 0x8f, 0x79, 0x4b, 0x32, 0xee, 0x03,
  0x99, 0xfd, 0x30, 0x49, 0xd1, 0x30, 0x76, 0x06, 0x08, 0x2b, 0x06, 0x01,
  0x05, 0x05, 0x07, 0x01, 0x01, 0x04, 0x6a, 0x30, 0x68, 0x30, 0x22, 0x06,
  0x08, 0x2b, 0x06, 0x01, 0x05, 0x05, 0x07, 0x30, 0x01, 0x86, 0x16, 0x68,
  0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x6f, 0x63, 0x73, 0x70, 0x2e, 0x74,
  0x68, 0x61, 0x77, 0x74, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x30, 0x42, 0x06,
  0x08, 0x2b, 0x06, 0x01, 0x05, 0x05, 0x07, 0x30, 0x02, 0x86, 0x36, 0x68,
  0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x74, 0x68,
  0x61, 0x77, 0x74, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x72, 0x65, 0x70,
  0x6f, 0x73, 0x69, 0x74, 0x6f, 0x72, 0x79, 0x2f, 0x54, 0x68, 0x61, 0x77,
  0x74, 0x65, 0x5f, 0x45, 0x56, 0x5f, 0x43, 0x41, 0x5f, 0x32, 0x30, 0x30,
  0x36, 0x2e, 0x63, 0x72, 0x74, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48,
  0x86, 0xf7, 0x0d, 0x01, 0x01, 0x05, 0x05, 0x00, 0x03, 0x82, 0x01, 0x01,
  0x00, 0xb2, 0xa0, 0x96, 0xdd, 0xec, 0x04, 0x38, 0x6b, 0xc3, 0x7a, 0xad,
  0x23, 0x44, 0x91, 0xe5, 0x62, 0x8c, 0xb1, 0xf6, 0x9c, 0x03, 0x21, 0x1f,
  0xef, 0x03, 0xd9, 0xca, 0x63, 0xb2, 0xf8, 0xdb, 0x5a, 0x93, 0xc2, 0xcc,
  0xf1, 0x7c, 0x6f, 0xeb, 0x0f, 0x51, 0x7b, 0x4b, 0xe7, 0xb5, 0xfc, 0xbc,
  0x9b, 0x87, 0x48, 0xcc, 0x5b, 0xf9, 0xc8, 0x66, 0xa4, 0x40, 0xac, 0xe9,
  0x42, 0x5d, 0xed, 0xf3, 0x53, 0x13, 0xe7, 0xbd, 0x6e, 0x7f, 0x50, 0x53,
  0x64, 0xb3, 0x95, 0xf1, 0x42, 0x4f, 0x36, 0x54, 0xb4, 0x1e, 0x7f, 0x18,
  0x37, 0x39, 0x3b, 0x06, 0x5b, 0xe5, 0x13, 0xd9, 0x57, 0xbc, 0xd5, 0x68,
  0xe3, 0x71, 0x5f, 0x5f, 0x2b, 0xf5, 0xa6, 0xc2, 0x8f, 0x67, 0x81, 0x3a,
  0x44, 0x63, 0x8c, 0x36, 0xfa, 0xa8, 0xed, 0xfd, 0xd7, 0x5e, 0xa2, 0x9f,
  0xb0, 0x9d, 0x47, 0x86, 0xfb, 0x71, 0x60, 0x8e, 0xc8, 0xd3, 0x45, 0x19,
  0xb7, 0xda, 0xcd, 0x9e, 0xea, 0x70, 0x10, 0x87, 0x37, 0x10, 0xdd, 0x2c,
  0x11, 0xdf, 0xee, 0x02, 0x21, 0xa6, 0x75, 0xe6, 0xd6, 0x9f, 0x54, 0x72,
  0x61, 0xe6, 0x5c, 0x1e, 0x6e, 0x16, 0xf6, 0x8e, 0xb8, 0xfc, 0x47, 0x80,
  0x05, 0x4b, 0xf7, 0x2d, 0x02, 0xee, 0x50, 0x26, 0xd1, 0x48, 0x01, 0x60,
  0xdc, 0x3c, 0xa7, 0xdb, 0xeb, 0xca, 0x8b, 0xa6, 0xff, 0x9e, 0x47, 0x5d,
  0x87, 0x40, 0xf8, 0xd2, 0x82, 0xd7, 0x13, 0x64, 0x0e, 0xd4, 0xb3, 0x29,
  0x22, 0xa7, 0xe0, 0xc8, 0xcd, 0x8c, 0x4d, 0xf5, 0x11, 0x21, 0x26, 0x02,
  0x43, 0x33, 0x8e, 0xa9, 0x3f, 0x91, 0xd4, 0x05, 0x97, 0xc9, 0xd3, 0x42,
  0x6b, 0x05, 0x99, 0xf6, 0x16, 0x71, 0x67, 0x65, 0xc7, 0x96, 0xdf, 0x2a,
  0xd7, 0x54, 0x63, 0x25, 0xc0, 0x28, 0xf7, 0x1c, 0xee, 0xcd, 0x8b, 0xe4,
  0x9d, 0x32, 0xa3, 0x81, 0x55
};

// A certificate for www.paypal.com with a NULL byte in the common name.
// From http://www.gossamer-threads.com/lists/fulldisc/full-disclosure/70363
unsigned char VARIABLE_IS_NOT_USED paypal_null_der[] = {
  0x30, 0x82, 0x06, 0x44, 0x30, 0x82, 0x05, 0xad, 0xa0, 0x03, 0x02, 0x01,
  0x02, 0x02, 0x03, 0x00, 0xf0, 0x9b, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86,
  0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x05, 0x05, 0x00, 0x30, 0x82, 0x01,
  0x12, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02,
  0x45, 0x53, 0x31, 0x12, 0x30, 0x10, 0x06, 0x03, 0x55, 0x04, 0x08, 0x13,
  0x09, 0x42, 0x61, 0x72, 0x63, 0x65, 0x6c, 0x6f, 0x6e, 0x61, 0x31, 0x12,
  0x30, 0x10, 0x06, 0x03, 0x55, 0x04, 0x07, 0x13, 0x09, 0x42, 0x61, 0x72,
  0x63, 0x65, 0x6c, 0x6f, 0x6e, 0x61, 0x31, 0x29, 0x30, 0x27, 0x06, 0x03,
  0x55, 0x04, 0x0a, 0x13, 0x20, 0x49, 0x50, 0x53, 0x20, 0x43, 0x65, 0x72,
  0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x41,
  0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x74, 0x79, 0x20, 0x73, 0x2e, 0x6c,
  0x2e, 0x31, 0x2e, 0x30, 0x2c, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x14, 0x25,
  0x67, 0x65, 0x6e, 0x65, 0x72, 0x61, 0x6c, 0x40, 0x69, 0x70, 0x73, 0x63,
  0x61, 0x2e, 0x63, 0x6f, 0x6d, 0x20, 0x43, 0x2e, 0x49, 0x2e, 0x46, 0x2e,
  0x20, 0x20, 0x42, 0x2d, 0x42, 0x36, 0x32, 0x32, 0x31, 0x30, 0x36, 0x39,
  0x35, 0x31, 0x2e, 0x30, 0x2c, 0x06, 0x03, 0x55, 0x04, 0x0b, 0x13, 0x25,
  0x69, 0x70, 0x73, 0x43, 0x41, 0x20, 0x43, 0x4c, 0x41, 0x53, 0x45, 0x41,
  0x31, 0x20, 0x43, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74,
  0x69, 0x6f, 0x6e, 0x20, 0x41, 0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x74,
  0x79, 0x31, 0x2e, 0x30, 0x2c, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x25,
  0x69, 0x70, 0x73, 0x43, 0x41, 0x20, 0x43, 0x4c, 0x41, 0x53, 0x45, 0x41,
  0x31, 0x20, 0x43, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74,
  0x69, 0x6f, 0x6e, 0x20, 0x41, 0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x74,
  0x79, 0x31, 0x20, 0x30, 0x1e, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7,
  0x0d, 0x01, 0x09, 0x01, 0x16, 0x11, 0x67, 0x65, 0x6e, 0x65, 0x72, 0x61,
  0x6c, 0x40, 0x69, 0x70, 0x73, 0x63, 0x61, 0x2e, 0x63, 0x6f, 0x6d, 0x30,
  0x1e, 0x17, 0x0d, 0x30, 0x39, 0x30, 0x32, 0x32, 0x34, 0x32, 0x33, 0x30,
  0x34, 0x31, 0x37, 0x5a, 0x17, 0x0d, 0x31, 0x31, 0x30, 0x32, 0x32, 0x34,
  0x32, 0x33, 0x30, 0x34, 0x31, 0x37, 0x5a, 0x30, 0x81, 0x94, 0x31, 0x0b,
  0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x55, 0x53, 0x31,
  0x13, 0x30, 0x11, 0x06, 0x03, 0x55, 0x04, 0x08, 0x13, 0x0a, 0x43, 0x61,
  0x6c, 0x69, 0x66, 0x6f, 0x72, 0x6e, 0x69, 0x61, 0x31, 0x16, 0x30, 0x14,
  0x06, 0x03, 0x55, 0x04, 0x07, 0x13, 0x0d, 0x53, 0x61, 0x6e, 0x20, 0x46,
  0x72, 0x61, 0x6e, 0x63, 0x69, 0x73, 0x63, 0x6f, 0x31, 0x11, 0x30, 0x0f,
  0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x08, 0x53, 0x65, 0x63, 0x75, 0x72,
  0x69, 0x74, 0x79, 0x31, 0x14, 0x30, 0x12, 0x06, 0x03, 0x55, 0x04, 0x0b,
  0x13, 0x0b, 0x53, 0x65, 0x63, 0x75, 0x72, 0x65, 0x20, 0x55, 0x6e, 0x69,
  0x74, 0x31, 0x2f, 0x30, 0x2d, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x26,
  0x77, 0x77, 0x77, 0x2e, 0x70, 0x61, 0x79, 0x70, 0x61, 0x6c, 0x2e, 0x63,
  0x6f, 0x6d, 0x00, 0x73, 0x73, 0x6c, 0x2e, 0x73, 0x65, 0x63, 0x75, 0x72,
  0x65, 0x63, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x2e,
  0x63, 0x63, 0x30, 0x81, 0x9f, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48,
  0x86, 0xf7, 0x0d, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x81, 0x8d, 0x00,
  0x30, 0x81, 0x89, 0x02, 0x81, 0x81, 0x00, 0xd2, 0x69, 0xfa, 0x6f, 0x3a,
  0x00, 0xb4, 0x21, 0x1b, 0xc8, 0xb1, 0x02, 0xd7, 0x3f, 0x19, 0xb2, 0xc4,
  0x6d, 0xb4, 0x54, 0xf8, 0x8b, 0x8a, 0xcc, 0xdb, 0x72, 0xc2, 0x9e, 0x3c,
  0x60, 0xb9, 0xc6, 0x91, 0x3d, 0x82, 0xb7, 0x7d, 0x99, 0xff, 0xd1, 0x29,
  0x84, 0xc1, 0x73, 0x53, 0x9c, 0x82, 0xdd, 0xfc, 0x24, 0x8c, 0x77, 0xd5,
  0x41, 0xf3, 0xe8, 0x1e, 0x42, 0xa1, 0xad, 0x2d, 0x9e, 0xff, 0x5b, 0x10,
  0x26, 0xce, 0x9d, 0x57, 0x17, 0x73, 0x16, 0x23, 0x38, 0xc8, 0xd6, 0xf1,
  0xba, 0xa3, 0x96, 0x5b, 0x16, 0x67, 0x4a, 0x4f, 0x73, 0x97, 0x3a, 0x4d,
  0x14, 0xa4, 0xf4, 0xe2, 0x3f, 0x8b, 0x05, 0x83, 0x42, 0xd1, 0xd0, 0xdc,
  0x2f, 0x7a, 0xe5, 0xb6, 0x10, 0xb2, 0x11, 0xc0, 0xdc, 0x21, 0x2a, 0x90,
  0xff, 0xae, 0x97, 0x71, 0x5a, 0x49, 0x81, 0xac, 0x40, 0xf3, 0x3b, 0xb8,
  0x59, 0xb2, 0x4f, 0x02, 0x03, 0x01, 0x00, 0x01, 0xa3, 0x82, 0x03, 0x21,
  0x30, 0x82, 0x03, 0x1d, 0x30, 0x09, 0x06, 0x03, 0x55, 0x1d, 0x13, 0x04,
  0x02, 0x30, 0x00, 0x30, 0x11, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x86,
  0xf8, 0x42, 0x01, 0x01, 0x04, 0x04, 0x03, 0x02, 0x06, 0x40, 0x30, 0x0b,
  0x06, 0x03, 0x55, 0x1d, 0x0f, 0x04, 0x04, 0x03, 0x02, 0x03, 0xf8, 0x30,
  0x13, 0x06, 0x03, 0x55, 0x1d, 0x25, 0x04, 0x0c, 0x30, 0x0a, 0x06, 0x08,
  0x2b, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x01, 0x30, 0x1d, 0x06, 0x03,
  0x55, 0x1d, 0x0e, 0x04, 0x16, 0x04, 0x14, 0x61, 0x8f, 0x61, 0x34, 0x43,
  0x55, 0x14, 0x7f, 0x27, 0x09, 0xce, 0x4c, 0x8b, 0xea, 0x9b, 0x7b, 0x19,
  0x25, 0xbc, 0x6e, 0x30, 0x1f, 0x06, 0x03, 0x55, 0x1d, 0x23, 0x04, 0x18,
  0x30, 0x16, 0x80, 0x14, 0x0e, 0x07, 0x60, 0xd4, 0x39, 0xc9, 0x1b, 0x5b,
  0x5d, 0x90, 0x7b, 0x23, 0xc8, 0xd2, 0x34, 0x9d, 0x4a, 0x9a, 0x46, 0x39,
  0x30, 0x09, 0x06, 0x03, 0x55, 0x1d, 0x11, 0x04, 0x02, 0x30, 0x00, 0x30,
  0x1c, 0x06, 0x03, 0x55, 0x1d, 0x12, 0x04, 0x15, 0x30, 0x13, 0x81, 0x11,
  0x67, 0x65, 0x6e, 0x65, 0x72, 0x61, 0x6c, 0x40, 0x69, 0x70, 0x73, 0x63,
  0x61, 0x2e, 0x63, 0x6f, 0x6d, 0x30, 0x72, 0x06, 0x09, 0x60, 0x86, 0x48,
  0x01, 0x86, 0xf8, 0x42, 0x01, 0x0d, 0x04, 0x65, 0x16, 0x63, 0x4f, 0x72,
  0x67, 0x61, 0x6e, 0x69, 0x7a, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x49,
  0x6e, 0x66, 0x6f, 0x72, 0x6d, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x4e,
  0x4f, 0x54, 0x20, 0x56, 0x41, 0x4c, 0x49, 0x44, 0x41, 0x54, 0x45, 0x44,
  0x2e, 0x20, 0x43, 0x4c, 0x41, 0x53, 0x45, 0x41, 0x31, 0x20, 0x53, 0x65,
  0x72, 0x76, 0x65, 0x72, 0x20, 0x43, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69,
  0x63, 0x61, 0x74, 0x65, 0x20, 0x69, 0x73, 0x73, 0x75, 0x65, 0x64, 0x20,
  0x62, 0x79, 0x20, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f, 0x77,
  0x77, 0x77, 0x2e, 0x69, 0x70, 0x73, 0x63, 0x61, 0x2e, 0x63, 0x6f, 0x6d,
  0x2f, 0x30, 0x2f, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x86, 0xf8, 0x42,
  0x01, 0x02, 0x04, 0x22, 0x16, 0x20, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a,
  0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x69, 0x70, 0x73, 0x63, 0x61, 0x2e,
  0x63, 0x6f, 0x6d, 0x2f, 0x69, 0x70, 0x73, 0x63, 0x61, 0x32, 0x30, 0x30,
  0x32, 0x2f, 0x30, 0x43, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x86, 0xf8,
  0x42, 0x01, 0x04, 0x04, 0x36, 0x16, 0x34, 0x68, 0x74, 0x74, 0x70, 0x73,
  0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x69, 0x70, 0x73, 0x63, 0x61,
  0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x69, 0x70, 0x73, 0x63, 0x61, 0x32, 0x30,
  0x30, 0x32, 0x2f, 0x69, 0x70, 0x73, 0x63, 0x61, 0x32, 0x30, 0x30, 0x32,
  0x43, 0x4c, 0x41, 0x53, 0x45, 0x41, 0x31, 0x2e, 0x63, 0x72, 0x6c, 0x30,
  0x46, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x86, 0xf8, 0x42, 0x01, 0x03,
  0x04, 0x39, 0x16, 0x37, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f,
  0x77, 0x77, 0x77, 0x2e, 0x69, 0x70, 0x73, 0x63, 0x61, 0x2e, 0x63, 0x6f,
  0x6d, 0x2f, 0x69, 0x70, 0x73, 0x63, 0x61, 0x32, 0x30, 0x30, 0x32, 0x2f,
  0x72, 0x65, 0x76, 0x6f, 0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x43, 0x4c,
  0x41, 0x53, 0x45, 0x41, 0x31, 0x2e, 0x68, 0x74, 0x6d, 0x6c, 0x3f, 0x30,
  0x43, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x86, 0xf8, 0x42, 0x01, 0x07,
  0x04, 0x36, 0x16, 0x34, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f,
  0x77, 0x77, 0x77, 0x2e, 0x69, 0x70, 0x73, 0x63, 0x61, 0x2e, 0x63, 0x6f,
  0x6d, 0x2f, 0x69, 0x70, 0x73, 0x63, 0x61, 0x32, 0x30, 0x30, 0x32, 0x2f,
  0x72, 0x65, 0x6e, 0x65, 0x77, 0x61, 0x6c, 0x43, 0x4c, 0x41, 0x53, 0x45,
  0x41, 0x31, 0x2e, 0x68, 0x74, 0x6d, 0x6c, 0x3f, 0x30, 0x41, 0x06, 0x09,
  0x60, 0x86, 0x48, 0x01, 0x86, 0xf8, 0x42, 0x01, 0x08, 0x04, 0x34, 0x16,
  0x32, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77,
  0x2e, 0x69, 0x70, 0x73, 0x63, 0x61, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x69,
  0x70, 0x73, 0x63, 0x61, 0x32, 0x30, 0x30, 0x32, 0x2f, 0x70, 0x6f, 0x6c,
  0x69, 0x63, 0x79, 0x43, 0x4c, 0x41, 0x53, 0x45, 0x41, 0x31, 0x2e, 0x68,
  0x74, 0x6d, 0x6c, 0x30, 0x81, 0x83, 0x06, 0x03, 0x55, 0x1d, 0x1f, 0x04,
  0x7c, 0x30, 0x7a, 0x30, 0x39, 0xa0, 0x37, 0xa0, 0x35, 0x86, 0x33, 0x68,
  0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x69, 0x70,
  0x73, 0x63, 0x61, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x69, 0x70, 0x73, 0x63,
  0x61, 0x32, 0x30, 0x30, 0x32, 0x2f, 0x69, 0x70, 0x73, 0x63, 0x61, 0x32,
  0x30, 0x30, 0x32, 0x43, 0x4c, 0x41, 0x53, 0x45, 0x41, 0x31, 0x2e, 0x63,
  0x72, 0x6c, 0x30, 0x3d, 0xa0, 0x3b, 0xa0, 0x39, 0x86, 0x37, 0x68, 0x74,
  0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x62, 0x61, 0x63, 0x6b,
  0x2e, 0x69, 0x70, 0x73, 0x63, 0x61, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x69,
  0x70, 0x73, 0x63, 0x61, 0x32, 0x30, 0x30, 0x32, 0x2f, 0x69, 0x70, 0x73,
  0x63, 0x61, 0x32, 0x30, 0x30, 0x32, 0x43, 0x4c, 0x41, 0x53, 0x45, 0x41,
  0x31, 0x2e, 0x63, 0x72, 0x6c, 0x30, 0x32, 0x06, 0x08, 0x2b, 0x06, 0x01,
  0x05, 0x05, 0x07, 0x01, 0x01, 0x04, 0x26, 0x30, 0x24, 0x30, 0x22, 0x06,
  0x08, 0x2b, 0x06, 0x01, 0x05, 0x05, 0x07, 0x30, 0x01, 0x86, 0x16, 0x68,
  0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x6f, 0x63, 0x73, 0x70, 0x2e, 0x69,
  0x70, 0x73, 0x63, 0x61, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x30, 0x0d, 0x06,
  0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x05, 0x05, 0x00,
  0x03, 0x81, 0x81, 0x00, 0x68, 0xee, 0x79, 0x97, 0x97, 0xdd, 0x3b, 0xef,
  0x16, 0x6a, 0x06, 0xf2, 0x14, 0x9a, 0x6e, 0xcd, 0x9e, 0x12, 0xf7, 0xaa,
  0x83, 0x10, 0xbd, 0xd1, 0x7c, 0x98, 0xfa, 0xc7, 0xae, 0xd4, 0x0e, 0x2c,
  0x9e, 0x38, 0x05, 0x9d, 0x52, 0x60, 0xa9, 0x99, 0x0a, 0x81, 0xb4, 0x98,
  0x90, 0x1d, 0xae, 0xbb, 0x4a, 0xd7, 0xb9, 0xdc, 0x88, 0x9e, 0x37, 0x78,
  0x41, 0x5b, 0xf7, 0x82, 0xa5, 0xf2, 0xba, 0x41, 0x25, 0x5a, 0x90, 0x1a,
  0x1e, 0x45, 0x38, 0xa1, 0x52, 0x58, 0x75, 0x94, 0x26, 0x44, 0xfb, 0x20,
  0x07, 0xba, 0x44, 0xcc, 0xe5, 0x4a, 0x2d, 0x72, 0x3f, 0x98, 0x47, 0xf6,
  0x26, 0xdc, 0x05, 0x46, 0x05, 0x07, 0x63, 0x21, 0xab, 0x46, 0x9b, 0x9c,
  0x78, 0xd5, 0x54, 0x5b, 0x3d, 0x0c, 0x1e, 0xc8, 0x64, 0x8c, 0xb5, 0x50,
  0x23, 0x82, 0x6f, 0xdb, 0xb8, 0x22, 0x1c, 0x43, 0x96, 0x07, 0xa8, 0xbb
};

}  // namespace
