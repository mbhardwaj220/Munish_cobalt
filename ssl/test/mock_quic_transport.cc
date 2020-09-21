/* Copyright (c) 2019, Google Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. */

#include "mock_quic_transport.h"

#include <openssl/span.h>

#include <cstring>
#include <limits>

namespace {

const uint8_t kTagHandshake = 'H';
const uint8_t kTagApplication = 'A';
const uint8_t kTagAlert = 'L';

}  // namespace

MockQuicTransport::MockQuicTransport(bssl::UniquePtr<BIO> bio, SSL *ssl)
    : bio_(std::move(bio)),
      read_levels_(ssl_encryption_application + 1),
      write_levels_(ssl_encryption_application + 1),
      ssl_(ssl) {}

bool MockQuicTransport::SetReadSecret(enum ssl_encryption_level_t level,
                                      const SSL_CIPHER *cipher,
                                      const uint8_t *secret,
                                      size_t secret_len) {
  // TODO(davidben): Assert the various encryption secret invariants.
  read_levels_[level].cipher = SSL_CIPHER_get_protocol_id(cipher);
  read_levels_[level].secret.assign(secret, secret + secret_len);
  return true;
}

bool MockQuicTransport::SetWriteSecret(enum ssl_encryption_level_t level,
                                       const SSL_CIPHER *cipher,
                                       const uint8_t *secret,
                                       size_t secret_len) {
  // TODO(davidben): Assert the various encryption secret invariants.
  write_levels_[level].cipher = SSL_CIPHER_get_protocol_id(cipher);
  write_levels_[level].secret.assign(secret, secret + secret_len);
  return true;
}

namespace {

bool ReadAll(BIO *bio, bssl::Span<uint8_t> out) {
  size_t len = out.size();
  uint8_t *buf = out.data();
  while (len > 0) {
    int chunk_len = std::numeric_limits<int>::max();
    if (len <= static_cast<unsigned int>(std::numeric_limits<int>::max())) {
      chunk_len = len;
    }
    int ret = BIO_read(bio, buf, chunk_len);
    if (ret <= 0) {
      return false;
    }
    buf += ret;
    len -= ret;
  }
  return true;
}

}  // namespace

bool MockQuicTransport::ReadHeader(uint8_t *out_tag, size_t *out_len) {
  uint8_t header[7];
  if (!ReadAll(bio_.get(), header)) {
    return false;
  }
  *out_tag = header[0];
  uint16_t cipher_suite = header[1] << 8 | header[2];
  size_t remaining_bytes =
      header[3] << 24 | header[4] << 16 | header[5] << 8 | header[6];

  enum ssl_encryption_level_t level = SSL_quic_read_level(ssl_);
  if (*out_tag == kTagApplication) {
    if (SSL_in_early_data(ssl_)) {
      level = ssl_encryption_early_data;
    } else {
      level = ssl_encryption_application;
    }
  }
  if (cipher_suite != read_levels_[level].cipher) {
    return false;
  }
  const std::vector<uint8_t> &secret = read_levels_[level].secret;
  std::vector<uint8_t> read_secret(secret.size());
  if (remaining_bytes < secret.size()) {
    return false;
  }
  remaining_bytes -= secret.size();
  if (!ReadAll(bio_.get(), bssl::MakeSpan(read_secret)) ||
      read_secret != secret) {
    return false;
  }
  *out_len = remaining_bytes;
  return true;
}

bool MockQuicTransport::ReadHandshake() {
  uint8_t tag;
  size_t len;
  if (!ReadHeader(&tag, &len)) {
    return false;
  }
  if (tag != kTagHandshake) {
    return false;
  }

  std::vector<uint8_t> buf(len);
  if (!ReadAll(bio_.get(), bssl::MakeSpan(buf))) {
    return false;
  }
  return SSL_provide_quic_data(ssl_, SSL_quic_read_level(ssl_), buf.data(),
                               buf.size());
}

int MockQuicTransport::ReadApplicationData(uint8_t *out, size_t max_out) {
  if (pending_app_data_.size() > 0) {
    size_t len = pending_app_data_.size() - app_data_offset_;
    if (len > max_out) {
      len = max_out;
    }
    memcpy(out, pending_app_data_.data() + app_data_offset_, len);
    app_data_offset_ += len;
    if (app_data_offset_ == pending_app_data_.size()) {
      pending_app_data_.clear();
      app_data_offset_ = 0;
    }
    return len;
  }

  uint8_t tag = 0;
  size_t len;
  while (true) {
    if (!ReadHeader(&tag, &len)) {
      // Assume that a failure to read the header means there's no more to read,
      // not an error reading.
      return 0;
    }
    if (tag == kTagApplication) {
      break;
    }
    if (tag != kTagHandshake) {
      return -1;
    }

    std::vector<uint8_t> buf(len);
    if (!ReadAll(bio_.get(), bssl::MakeSpan(buf))) {
      return -1;
    }
    if (SSL_provide_quic_data(ssl_, SSL_quic_read_level(ssl_), buf.data(),
                              buf.size()) != 1) {
      return -1;
    }
    if (SSL_in_init(ssl_)) {
      int ret = SSL_do_handshake(ssl_);
      if (ret < 0) {
        int ssl_err = SSL_get_error(ssl_, ret);
        if (ssl_err == SSL_ERROR_WANT_READ) {
          continue;
        }
        return -1;
      }
    } else if (SSL_process_quic_post_handshake(ssl_) != 1) {
      return -1;
    }
  }

  uint8_t *buf = out;
  if (len > max_out) {
    pending_app_data_.resize(len);
    buf = pending_app_data_.data();
  }
  app_data_offset_ = 0;
  if (!ReadAll(bio_.get(), bssl::MakeSpan(buf, len))) {
    return -1;
  }
  if (len > max_out) {
    memcpy(out, buf, max_out);
    app_data_offset_ = max_out;
    return max_out;
  }
  return len;
}

bool MockQuicTransport::WriteRecord(enum ssl_encryption_level_t level,
                                    uint8_t tag, const uint8_t *data,
                                    size_t len) {
  uint16_t cipher_suite = write_levels_[level].cipher;
  const std::vector<uint8_t> &secret = write_levels_[level].secret;
  size_t tlv_len = secret.size() + len;
  uint8_t header[7];
  header[0] = tag;
  header[1] = (cipher_suite >> 8) & 0xff;
  header[2] = cipher_suite & 0xff;
  header[3] = (tlv_len >> 24) & 0xff;
  header[4] = (tlv_len >> 16) & 0xff;
  header[5] = (tlv_len >> 8) & 0xff;
  header[6] = tlv_len & 0xff;
  return BIO_write_all(bio_.get(), header, sizeof(header)) &&
         BIO_write_all(bio_.get(), secret.data(), secret.size()) &&
         BIO_write_all(bio_.get(), data, len);
}

bool MockQuicTransport::WriteHandshakeData(enum ssl_encryption_level_t level,
                                           const uint8_t *data, size_t len) {
  return WriteRecord(level, kTagHandshake, data, len);
}

bool MockQuicTransport::WriteApplicationData(const uint8_t *in, size_t len) {
  enum ssl_encryption_level_t level = ssl_encryption_application;
  if (SSL_in_early_data(ssl_) && !SSL_is_server(ssl_)) {
    level = ssl_encryption_early_data;
  }
  return WriteRecord(level, kTagApplication, in, len);
}

bool MockQuicTransport::Flush() { return BIO_flush(bio_.get()); }

bool MockQuicTransport::SendAlert(enum ssl_encryption_level_t level,
                                  uint8_t alert) {
  uint8_t alert_msg[] = {2, alert};
  return WriteRecord(level, kTagAlert, alert_msg, sizeof(alert_msg));
}
