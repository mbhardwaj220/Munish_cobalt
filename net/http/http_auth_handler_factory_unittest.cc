// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/scoped_ptr.h"
#include "net/base/net_errors.h"
#include "net/http/http_auth_handler.h"
#include "net/http/http_auth_handler_factory.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace net {

class MockHttpAuthHandlerFactory : public HttpAuthHandlerFactory {
 public:
  explicit MockHttpAuthHandlerFactory(int return_code) :
      return_code_(return_code) {}
  virtual ~MockHttpAuthHandlerFactory() {}

  virtual int CreateAuthHandler(HttpAuth::ChallengeTokenizer* challenge,
                                HttpAuth::Target target,
                                const GURL& origin,
                                CreateReason reason,
                                int nonce_count,
                                const BoundNetLog& net_log,
                                scoped_refptr<HttpAuthHandler>* handler) {
    *handler = NULL;
    return return_code_;
  }

 private:
  int return_code_;
};

TEST(HttpAuthHandlerFactoryTest, RegistryFactory) {
  HttpAuthHandlerRegistryFactory registry_factory;
  GURL gurl("www.google.com");
  const int kBasicReturnCode = ERR_INVALID_SPDY_STREAM;
  MockHttpAuthHandlerFactory* mock_factory_basic =
      new MockHttpAuthHandlerFactory(kBasicReturnCode);

  const int kDigestReturnCode = ERR_PAC_SCRIPT_FAILED;
  MockHttpAuthHandlerFactory* mock_factory_digest =
      new MockHttpAuthHandlerFactory(kDigestReturnCode);

  const int kDigestReturnCodeReplace = ERR_SYN_REPLY_NOT_RECEIVED;
  MockHttpAuthHandlerFactory* mock_factory_digest_replace =
      new MockHttpAuthHandlerFactory(kDigestReturnCodeReplace);

  scoped_refptr<HttpAuthHandler> handler;

  // No schemes should be supported in the beginning.
  EXPECT_EQ(ERR_UNSUPPORTED_AUTH_SCHEME,
            registry_factory.CreateAuthHandlerFromString(
                "Basic", HttpAuth::AUTH_SERVER, gurl, BoundNetLog(), &handler));

  // Test what happens with a single scheme.
  registry_factory.RegisterSchemeFactory("Basic", mock_factory_basic);
  EXPECT_EQ(kBasicReturnCode,
            registry_factory.CreateAuthHandlerFromString(
                "Basic", HttpAuth::AUTH_SERVER, gurl, BoundNetLog(), &handler));
  EXPECT_EQ(ERR_UNSUPPORTED_AUTH_SCHEME,
            registry_factory.CreateAuthHandlerFromString(
                "Digest", HttpAuth::AUTH_SERVER, gurl, BoundNetLog(),
                &handler));

  // Test multiple schemes
  registry_factory.RegisterSchemeFactory("Digest", mock_factory_digest);
  EXPECT_EQ(kBasicReturnCode,
            registry_factory.CreateAuthHandlerFromString(
                "Basic", HttpAuth::AUTH_SERVER, gurl, BoundNetLog(), &handler));
  EXPECT_EQ(kDigestReturnCode,
            registry_factory.CreateAuthHandlerFromString(
                "Digest", HttpAuth::AUTH_SERVER, gurl, BoundNetLog(),
                &handler));

  // Test case-insensitivity
  EXPECT_EQ(kBasicReturnCode,
            registry_factory.CreateAuthHandlerFromString(
                "basic", HttpAuth::AUTH_SERVER, gurl, BoundNetLog(), &handler));

  // Test replacement of existing auth scheme
  registry_factory.RegisterSchemeFactory("Digest", mock_factory_digest_replace);
  EXPECT_EQ(kBasicReturnCode,
            registry_factory.CreateAuthHandlerFromString(
                "Basic", HttpAuth::AUTH_SERVER, gurl, BoundNetLog(), &handler));
  EXPECT_EQ(kDigestReturnCodeReplace,
            registry_factory.CreateAuthHandlerFromString(
                "Digest", HttpAuth::AUTH_SERVER, gurl, BoundNetLog(),
                &handler));
}

TEST(HttpAuthHandlerFactoryTest, DefaultFactory) {
  scoped_ptr<HttpAuthHandlerFactory> http_auth_handler_factory(
      HttpAuthHandlerFactory::CreateDefault());

  GURL server_origin("http://www.example.com");
  GURL proxy_origin("http://cache.example.com:3128");
  {
    scoped_refptr<HttpAuthHandler> handler;
    int rv = http_auth_handler_factory->CreateAuthHandlerFromString(
        "Basic realm=\"FooBar\"",
        HttpAuth::AUTH_SERVER,
        server_origin,
        BoundNetLog(),
        &handler);
    EXPECT_EQ(OK, rv);
    EXPECT_FALSE(handler.get() == NULL);
    EXPECT_STREQ("basic", handler->scheme().c_str());
    EXPECT_STREQ("FooBar", handler->realm().c_str());
    EXPECT_EQ(HttpAuth::AUTH_SERVER, handler->target());
    EXPECT_FALSE(handler->encrypts_identity());
    EXPECT_FALSE(handler->is_connection_based());
  }
  {
    scoped_refptr<HttpAuthHandler> handler;
    int rv = http_auth_handler_factory->CreateAuthHandlerFromString(
        "UNSUPPORTED realm=\"FooBar\"",
        HttpAuth::AUTH_SERVER,
        server_origin,
        BoundNetLog(),
        &handler);
    EXPECT_EQ(ERR_UNSUPPORTED_AUTH_SCHEME, rv);
    EXPECT_TRUE(handler.get() == NULL);
  }
  {
    scoped_refptr<HttpAuthHandler> handler;
    int rv = http_auth_handler_factory->CreateAuthHandlerFromString(
        "Digest realm=\"FooBar\", nonce=\"xyz\"",
        HttpAuth::AUTH_PROXY,
        proxy_origin,
        BoundNetLog(),
        &handler);
    EXPECT_EQ(OK, rv);
    EXPECT_FALSE(handler.get() == NULL);
    EXPECT_STREQ("digest", handler->scheme().c_str());
    EXPECT_STREQ("FooBar", handler->realm().c_str());
    EXPECT_EQ(HttpAuth::AUTH_PROXY, handler->target());
    EXPECT_TRUE(handler->encrypts_identity());
    EXPECT_FALSE(handler->is_connection_based());
  }
  {
    scoped_refptr<HttpAuthHandler> handler;
    int rv = http_auth_handler_factory->CreateAuthHandlerFromString(
        "NTLM",
        HttpAuth::AUTH_SERVER,
        server_origin,
        BoundNetLog(),
        &handler);
    EXPECT_EQ(OK, rv);
    ASSERT_FALSE(handler.get() == NULL);
    EXPECT_STREQ("ntlm", handler->scheme().c_str());
    EXPECT_STREQ("", handler->realm().c_str());
    EXPECT_EQ(HttpAuth::AUTH_SERVER, handler->target());
    EXPECT_TRUE(handler->encrypts_identity());
    EXPECT_TRUE(handler->is_connection_based());
  }
#if defined(OS_WIN)
  {
    scoped_refptr<HttpAuthHandler> handler;
    int rv = http_auth_handler_factory->CreateAuthHandlerFromString(
        "Negotiate",
        HttpAuth::AUTH_SERVER,
        server_origin,
        BoundNetLog(),
        &handler);
    EXPECT_EQ(OK, rv);
    EXPECT_FALSE(handler.get() == NULL);
    EXPECT_STREQ("negotiate", handler->scheme().c_str());
    EXPECT_STREQ("", handler->realm().c_str());
    EXPECT_EQ(HttpAuth::AUTH_SERVER, handler->target());
    EXPECT_TRUE(handler->encrypts_identity());
    EXPECT_TRUE(handler->is_connection_based());
  }
#else  // !defined(OS_WIN)
  {
    scoped_refptr<HttpAuthHandler> handler;
    int rv = http_auth_handler_factory->CreateAuthHandlerFromString(
        "Negotiate",
        HttpAuth::AUTH_SERVER,
        server_origin,
        BoundNetLog(),
        &handler);
    EXPECT_EQ(ERR_UNSUPPORTED_AUTH_SCHEME, rv);
    EXPECT_TRUE(handler.get() == NULL);
  }
#endif  // !defined(OS_WIN)
}

}  // namespace net
