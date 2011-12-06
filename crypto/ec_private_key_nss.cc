// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "crypto/ec_private_key.h"

extern "C" {
// Work around NSS missing SEC_BEGIN_PROTOS in secmodt.h.  This must come before
// other NSS headers.
#include <secmodt.h>
}

#include <cryptohi.h>
#include <keyhi.h>
#include <pk11pub.h>
#include <secmod.h>

#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "crypto/nss_util.h"
#include "crypto/nss_util_internal.h"
#include "crypto/scoped_nss_types.h"
#include "crypto/third_party/nss/chromium-nss.h"

namespace {

// Copied from rsa_private_key_nss.cc.
static bool ReadAttribute(SECKEYPrivateKey* key,
                          CK_ATTRIBUTE_TYPE type,
                          std::vector<uint8>* output) {
  SECItem item;
  SECStatus rv;
  rv = PK11_ReadRawAttribute(PK11_TypePrivKey, key, type, &item);
  if (rv != SECSuccess) {
    DLOG(ERROR) << "PK11_ReadRawAttribute: " << PORT_GetError();
    return false;
  }

  output->assign(item.data, item.data + item.len);
  SECITEM_FreeItem(&item, PR_FALSE);
  return true;
}

}  // namespace

namespace crypto {

ECPrivateKey::~ECPrivateKey() {
  if (key_)
    SECKEY_DestroyPrivateKey(key_);
  if (public_key_)
    SECKEY_DestroyPublicKey(public_key_);
}

// static
ECPrivateKey* ECPrivateKey::Create() {
  return CreateWithParams(PR_FALSE /* not permanent */,
                          PR_FALSE /* not sensitive */);
}

// static
ECPrivateKey* ECPrivateKey::CreateSensitive() {
#if defined(USE_NSS)
  return CreateWithParams(PR_TRUE /* permanent */,
                          PR_TRUE /* sensitive */);
#else
  // If USE_NSS is not defined, we initialize NSS with no databases, so we can't
  // create permanent keys.
  NOTREACHED();
  return NULL;
#endif
}

// static
ECPrivateKey* ECPrivateKey::CreateFromEncryptedPrivateKeyInfo(
    const std::string& password,
    const std::vector<uint8>& encrypted_private_key_info,
    const std::vector<uint8>& subject_public_key_info) {
  return CreateFromEncryptedPrivateKeyInfoWithParams(
      password,
      encrypted_private_key_info,
      subject_public_key_info,
      PR_FALSE /* not permanent */,
      PR_FALSE /* not sensitive */);
}

// static
ECPrivateKey* ECPrivateKey::CreateSensitiveFromEncryptedPrivateKeyInfo(
    const std::string& password,
    const std::vector<uint8>& encrypted_private_key_info,
    const std::vector<uint8>& subject_public_key_info) {
#if defined(USE_NSS)
  return CreateFromEncryptedPrivateKeyInfoWithParams(
      password,
      encrypted_private_key_info,
      subject_public_key_info,
      PR_TRUE /* permanent */,
      PR_TRUE /* sensitive */);
#else
  // If USE_NSS is not defined, we initialize NSS with no databases, so we can't
  // create permanent keys.
  NOTREACHED();
  return NULL;
#endif
}

// static
bool ECPrivateKey::ImportFromEncryptedPrivateKeyInfo(
    const std::string& password,
    const uint8* encrypted_private_key_info,
    size_t encrypted_private_key_info_len,
    CERTSubjectPublicKeyInfo* decoded_spki,
    bool permanent,
    bool sensitive,
    SECKEYPrivateKey** key,
    SECKEYPublicKey** public_key) {
  ScopedPK11Slot slot(GetPrivateNSSKeySlot());
  if (!slot.get())
    return false;

  *public_key = SECKEY_ExtractPublicKey(decoded_spki);

  if (!*public_key) {
    DLOG(ERROR) << "SECKEY_ExtractPublicKey: " << PORT_GetError();
    return false;
  }

  SECItem encoded_epki = {
    siBuffer,
    const_cast<unsigned char*>(encrypted_private_key_info),
    encrypted_private_key_info_len
  };
  SECKEYEncryptedPrivateKeyInfo epki;
  memset(&epki, 0, sizeof(epki));

  ScopedPLArenaPool arena(PORT_NewArena(DER_DEFAULT_CHUNKSIZE));

  SECStatus rv = SEC_QuickDERDecodeItem(
      arena.get(),
      &epki,
      SEC_ASN1_GET(SECKEY_EncryptedPrivateKeyInfoTemplate),
      &encoded_epki);
  if (rv != SECSuccess) {
    DLOG(ERROR) << "SEC_QuickDERDecodeItem: " << PORT_GetError();
    SECKEY_DestroyPublicKey(*public_key);
    *public_key = NULL;
    return false;
  }

  SECItem password_item = {
    siBuffer,
    reinterpret_cast<unsigned char*>(const_cast<char*>(password.data())),
    password.size()
  };

  rv = ImportEncryptedECPrivateKeyInfoAndReturnKey(
      slot.get(),
      &epki,
      &password_item,
      NULL,  // nickname
      &(*public_key)->u.ec.publicValue,
      permanent,
      sensitive,
      key,
      NULL);  // wincx
  if (rv != SECSuccess) {
    DLOG(ERROR) << "ImportEncryptedECPrivateKeyInfoAndReturnKey: "
                << PORT_GetError();
    SECKEY_DestroyPublicKey(*public_key);
    *public_key = NULL;
    return false;
  }

  return true;
}

bool ECPrivateKey::ExportEncryptedPrivateKey(
    const std::string& password,
    int iterations,
    std::vector<uint8>* output) {
  // We export as an EncryptedPrivateKeyInfo bundle instead of a plain PKCS #8
  // PrivateKeyInfo because PK11_ImportDERPrivateKeyInfoAndReturnKey doesn't
  // support EC keys.
  // https://bugzilla.mozilla.org/show_bug.cgi?id=327773
  SECItem password_item = {
    siBuffer,
    reinterpret_cast<unsigned char*>(const_cast<char*>(password.data())),
    password.size()
  };

  SECKEYEncryptedPrivateKeyInfo* encrypted = PK11_ExportEncryptedPrivKeyInfo(
      NULL, // Slot, optional.
      SEC_OID_PKCS12_V2_PBE_WITH_SHA1_AND_3KEY_TRIPLE_DES_CBC,
      &password_item,
      key_,
      iterations,
      NULL); // wincx.

  if (!encrypted) {
    DLOG(ERROR) << "PK11_ExportEncryptedPrivKeyInfo: " << PORT_GetError();
    return false;
  }

  ScopedPLArenaPool arena(PORT_NewArena(DER_DEFAULT_CHUNKSIZE));
  SECItem der_key = {siBuffer, NULL, 0};
  SECItem* encoded_item = SEC_ASN1EncodeItem(
      arena.get(),
      &der_key,
      encrypted,
      SEC_ASN1_GET(SECKEY_EncryptedPrivateKeyInfoTemplate));
  SECKEY_DestroyEncryptedPrivateKeyInfo(encrypted, PR_TRUE);
  if (!encoded_item) {
    DLOG(ERROR) << "SEC_ASN1EncodeItem: " << PORT_GetError();
    return false;
  }

  output->assign(der_key.data, der_key.data + der_key.len);

  return true;
}

bool ECPrivateKey::ExportPublicKey(std::vector<uint8>* output) {
  ScopedSECItem der_pubkey(
      SECKEY_EncodeDERSubjectPublicKeyInfo(public_key_));
  if (!der_pubkey.get()) {
    return false;
  }

  output->assign(der_pubkey->data, der_pubkey->data + der_pubkey->len);
  return true;
}

bool ECPrivateKey::ExportValue(std::vector<uint8>* output) {
  return ReadAttribute(key_, CKA_VALUE, output);
}

bool ECPrivateKey::ExportECParams(std::vector<uint8>* output) {
  return ReadAttribute(key_, CKA_EC_PARAMS, output);
}

ECPrivateKey::ECPrivateKey() : key_(NULL), public_key_(NULL) {}

// static
ECPrivateKey* ECPrivateKey::CreateWithParams(bool permanent,
                                             bool sensitive) {
  EnsureNSSInit();

  scoped_ptr<ECPrivateKey> result(new ECPrivateKey);

  ScopedPK11Slot slot(GetPrivateNSSKeySlot());
  if (!slot.get())
    return NULL;

  SECOidData* oid_data = SECOID_FindOIDByTag(SEC_OID_SECG_EC_SECP256R1);
  if (!oid_data) {
    DLOG(ERROR) << "SECOID_FindOIDByTag: " << PORT_GetError();
    return NULL;
  }

  // SECKEYECParams is a SECItem containing the DER encoded ASN.1 ECParameters
  // value.  For a named curve, that is just the OBJECT IDENTIFIER of the curve.
  // In addition to the oid data, the encoding requires one byte for the ASN.1
  // tag and one byte for the length (assuming the length is <= 127).
  DCHECK_LE(oid_data->oid.len, 127U);
  std::vector<unsigned char> parameters_buf(2 + oid_data->oid.len);
  SECKEYECParams ec_parameters = {
    siDEROID, &parameters_buf[0], parameters_buf.size()
  };

  ec_parameters.data[0] = SEC_ASN1_OBJECT_ID;
  ec_parameters.data[1] = oid_data->oid.len;
  memcpy(ec_parameters.data + 2, oid_data->oid.data, oid_data->oid.len);

  result->key_ = PK11_GenerateKeyPair(slot.get(),
                                      CKM_EC_KEY_PAIR_GEN,
                                      &ec_parameters,
                                      &result->public_key_,
                                      permanent,
                                      sensitive,
                                      NULL);
  if (!result->key_) {
    DLOG(ERROR) << "PK11_GenerateKeyPair: " << PORT_GetError();
    return NULL;
  }

  return result.release();
}

// static
ECPrivateKey* ECPrivateKey::CreateFromEncryptedPrivateKeyInfoWithParams(
    const std::string& password,
    const std::vector<uint8>& encrypted_private_key_info,
    const std::vector<uint8>& subject_public_key_info,
    bool permanent,
    bool sensitive) {
  EnsureNSSInit();

  scoped_ptr<ECPrivateKey> result(new ECPrivateKey);

  SECItem encoded_spki = {
    siBuffer,
    const_cast<unsigned char*>(&subject_public_key_info[0]),
    subject_public_key_info.size()
  };
  CERTSubjectPublicKeyInfo* decoded_spki = SECKEY_DecodeDERSubjectPublicKeyInfo(
      &encoded_spki);
  if (!decoded_spki) {
    DLOG(ERROR) << "SECKEY_DecodeDERSubjectPublicKeyInfo: " << PORT_GetError();
    return NULL;
  }

  bool success = ECPrivateKey::ImportFromEncryptedPrivateKeyInfo(
      password,
      &encrypted_private_key_info[0],
      encrypted_private_key_info.size(),
      decoded_spki,
      permanent,
      sensitive,
      &result->key_,
      &result->public_key_);

  SECKEY_DestroySubjectPublicKeyInfo(decoded_spki);

  if (success)
    return result.release();

  return NULL;
}

}  // namespace crypto
