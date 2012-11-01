// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_ANDROID_NETWORK_LIBRARY_H_
#define NET_ANDROID_NETWORK_LIBRARY_H_

#include <jni.h>

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "net/base/net_export.h"

namespace net {
namespace android {

enum VerifyResult {
  // Certificate verification was successful.
  VERIFY_OK,
  // Certificate verification was failed. There is no detail error information
  // given by Android API.
  VERIFY_NO_TRUSTED_ROOT,
  // Error occurs when invoke JNI methods.
  VERIFY_INVOCATION_ERROR,
};

// |cert_chain| is DER encoded chain of certificates, with the server's own
// certificate listed first.
// |auth_type| is as per the Java X509Certificate.checkServerTrusted method.

VerifyResult VerifyX509CertChain(const std::vector<std::string>& cert_chain,
                                 const std::string& auth_type);

// Helper for the <keygen> handler. Passes the DER-encoded key  pair via
// JNI to the Credentials store. Note that the public key must be a DER
// encoded SubjectPublicKeyInfo (X.509), as returned by i2d_PUBKEY()
// (and *not* i2d_PublicKey(), which returns a PKCS#1 key).
//
// Also, the private key must be in PKCS#8 format, as returned by
// i2d_PKCS8_PRIV_KEY_INFO(EVP_PKEY2PKCS8(pkey)), which is a different
// format than what i2d_PrivateKey() returns, so don't use it either.
//
bool StoreKeyPair(const uint8* public_key,
                  size_t public_len,
                  const uint8* private_key,
                  size_t private_len);

// Returns true if it can determine that only loopback addresses are configured.
// i.e. if only 127.0.0.1 and ::1 are routable.
// Also returns false if it cannot determine this.
bool HaveOnlyLoopbackAddresses();

// Return a string containing a list of network interfaces, each item is a
// network name and address pair.
// e.g. "eth0,10.0.0.2;eth0,fe80::5054:ff:fe12:3456" is a result string
// containing two items.
std::string GetNetworkList();

// Get the mime type (if any) that is associated with the file extension.
// Returns true if a corresponding mime type exists.
bool GetMimeTypeFromExtension(const std::string& extension,
                              std::string* result);

// Register JNI methods
NET_EXPORT bool RegisterNetworkLibrary(JNIEnv* env);

}  // namespace android
}  // namespace net

#endif  // NET_ANDROID_NETWORK_LIBRARY_H_
