// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/base/cert_verify_result.h"

#include "net/base/x509_certificate.h"

namespace net {

CertVerifyResult::CertVerifyResult() {
  Reset();
}

CertVerifyResult::~CertVerifyResult() {
}

void CertVerifyResult::Reset() {
  verified_cert = NULL;
  cert_status = 0;
  has_md5 = false;
  has_md2 = false;
  has_md4 = false;
  has_md5_ca = false;
  has_md2_ca = false;
  is_issued_by_known_root = false;

  public_key_hashes.clear();
  public_key_hashes.reserve(FINGERPRINT_TAGS_COUNT);
  HashValueVector sha1s;
  public_key_hashes.push_back(sha1s);
  HashValueVector sha256s;
  public_key_hashes.push_back(sha256s);
}

}  // namespace net
