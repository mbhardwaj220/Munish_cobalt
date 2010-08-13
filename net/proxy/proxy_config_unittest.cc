// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/proxy/proxy_config.h"
#include "net/proxy/proxy_config_service_common_unittest.h"
#include "net/proxy/proxy_info.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace net {
namespace {

void ExpectProxyServerEquals(const char* expectation,
                             const ProxyServer& proxy_server) {
  if (expectation == NULL) {
    EXPECT_FALSE(proxy_server.is_valid());
  } else {
    EXPECT_EQ(expectation, proxy_server.ToURI());
  }
}

TEST(ProxyConfigTest, Equals) {
  // Test |ProxyConfig::auto_detect|.

  ProxyConfig config1;
  config1.set_auto_detect(true);

  ProxyConfig config2;
  config2.set_auto_detect(false);

  EXPECT_FALSE(config1.Equals(config2));
  EXPECT_FALSE(config2.Equals(config1));

  config2.set_auto_detect(true);

  EXPECT_TRUE(config1.Equals(config2));
  EXPECT_TRUE(config2.Equals(config1));

  // Test |ProxyConfig::pac_url|.

  config2.set_pac_url(GURL("http://wpad/wpad.dat"));

  EXPECT_FALSE(config1.Equals(config2));
  EXPECT_FALSE(config2.Equals(config1));

  config1.set_pac_url(GURL("http://wpad/wpad.dat"));

  EXPECT_TRUE(config1.Equals(config2));
  EXPECT_TRUE(config2.Equals(config1));

  // Test |ProxyConfig::proxy_rules|.

  config2.proxy_rules().type = ProxyConfig::ProxyRules::TYPE_SINGLE_PROXY;
  config2.proxy_rules().single_proxy =
      ProxyServer::FromURI("myproxy:80", ProxyServer::SCHEME_HTTP);

  EXPECT_FALSE(config1.Equals(config2));
  EXPECT_FALSE(config2.Equals(config1));

  config1.proxy_rules().type = ProxyConfig::ProxyRules::TYPE_SINGLE_PROXY;
  config1.proxy_rules().single_proxy =
      ProxyServer::FromURI("myproxy:100", ProxyServer::SCHEME_HTTP);

  EXPECT_FALSE(config1.Equals(config2));
  EXPECT_FALSE(config2.Equals(config1));

  config1.proxy_rules().single_proxy =
      ProxyServer::FromURI("myproxy", ProxyServer::SCHEME_HTTP);

  EXPECT_TRUE(config1.Equals(config2));
  EXPECT_TRUE(config2.Equals(config1));

  // Test |ProxyConfig::bypass_rules|.

  config2.proxy_rules().bypass_rules.AddRuleFromString("*.google.com");

  EXPECT_FALSE(config1.Equals(config2));
  EXPECT_FALSE(config2.Equals(config1));

  config1.proxy_rules().bypass_rules.AddRuleFromString("*.google.com");

  EXPECT_TRUE(config1.Equals(config2));
  EXPECT_TRUE(config2.Equals(config1));

  // Test |ProxyConfig::proxy_rules.reverse_bypass|.

  config2.proxy_rules().reverse_bypass = true;

  EXPECT_FALSE(config1.Equals(config2));
  EXPECT_FALSE(config2.Equals(config1));

  config1.proxy_rules().reverse_bypass = true;

  EXPECT_TRUE(config1.Equals(config2));
  EXPECT_TRUE(config2.Equals(config1));
}

TEST(ProxyConfigTest, ParseProxyRules) {
  const struct {
    const char* proxy_rules;

    ProxyConfig::ProxyRules::Type type;
    const char* single_proxy;
    const char* proxy_for_http;
    const char* proxy_for_https;
    const char* proxy_for_ftp;
    const char* socks_proxy;
  } tests[] = {
    // One HTTP proxy for all schemes.
    {
      "myproxy:80",

      ProxyConfig::ProxyRules::TYPE_SINGLE_PROXY,
      "myproxy:80",
      NULL,
      NULL,
      NULL,
      NULL,
    },

    // Only specify a proxy server for "http://" urls.
    {
      "http=myproxy:80",

      ProxyConfig::ProxyRules::TYPE_PROXY_PER_SCHEME,
      NULL,
      "myproxy:80",
      NULL,
      NULL,
      NULL,
    },

    // Specify an HTTP proxy for "ftp://" and a SOCKS proxy for "https://" urls.
    {
      "ftp=ftp-proxy ; https=socks4://foopy",

      ProxyConfig::ProxyRules::TYPE_PROXY_PER_SCHEME,
      NULL,
      NULL,
      "socks4://foopy:1080",
      "ftp-proxy:80",
      NULL,
    },

    // Give a scheme-specific proxy as well as a non-scheme specific.
    // The first entry "foopy" takes precedance marking this list as
    // TYPE_SINGLE_PROXY.
    {
      "foopy ; ftp=ftp-proxy",

      ProxyConfig::ProxyRules::TYPE_SINGLE_PROXY,
      "foopy:80",
      NULL,
      NULL,
      NULL,
      NULL,
    },

    // Give a scheme-specific proxy as well as a non-scheme specific.
    // The first entry "ftp=ftp-proxy" takes precedance marking this list as
    // TYPE_PROXY_PER_SCHEME.
    {
      "ftp=ftp-proxy ; foopy",

      ProxyConfig::ProxyRules::TYPE_PROXY_PER_SCHEME,
      NULL,
      NULL,
      NULL,
      "ftp-proxy:80",
      NULL,
    },

    // Include duplicate entries -- last one wins.
    {
      "ftp=ftp1 ; ftp=ftp2 ; ftp=ftp3",

      ProxyConfig::ProxyRules::TYPE_PROXY_PER_SCHEME,
      NULL,
      NULL,
      NULL,
      "ftp3:80",
      NULL,
    },

    // Only SOCKS proxy present, others being blank.
    {
      "socks=foopy",

      ProxyConfig::ProxyRules::TYPE_PROXY_PER_SCHEME,
      NULL,
      NULL,
      NULL,
      NULL,
      "socks4://foopy:1080",
      },

    // SOCKS proxy present along with other proxies too
    {
      "http=httpproxy ; https=httpsproxy ; ftp=ftpproxy ; socks=foopy ",

      ProxyConfig::ProxyRules::TYPE_PROXY_PER_SCHEME,
      NULL,
      "httpproxy:80",
      "httpsproxy:80",
      "ftpproxy:80",
      "socks4://foopy:1080",
    },

    // SOCKS proxy (with modifier) present along with some proxies
    // (FTP being blank)
    {
      "http=httpproxy ; https=httpsproxy ; socks=socks5://foopy ",

      ProxyConfig::ProxyRules::TYPE_PROXY_PER_SCHEME,
      NULL,
      "httpproxy:80",
      "httpsproxy:80",
      NULL,
      "socks5://foopy:1080",
      },

    // Include unsupported schemes -- they are discarded.
    {
      "crazy=foopy ; foo=bar ; https=myhttpsproxy",

      ProxyConfig::ProxyRules::TYPE_PROXY_PER_SCHEME,
      NULL,
      NULL,
      "myhttpsproxy:80",
      NULL,
      NULL,
    },
  };

  ProxyConfig config;

  for (size_t i = 0; i < ARRAYSIZE_UNSAFE(tests); ++i) {
    config.proxy_rules().ParseFromString(tests[i].proxy_rules);

    EXPECT_EQ(tests[i].type, config.proxy_rules().type);
    ExpectProxyServerEquals(tests[i].single_proxy,
                            config.proxy_rules().single_proxy);
    ExpectProxyServerEquals(tests[i].proxy_for_http,
                            config.proxy_rules().proxy_for_http);
    ExpectProxyServerEquals(tests[i].proxy_for_https,
                            config.proxy_rules().proxy_for_https);
    ExpectProxyServerEquals(tests[i].proxy_for_ftp,
                            config.proxy_rules().proxy_for_ftp);
    ExpectProxyServerEquals(tests[i].socks_proxy,
                            config.proxy_rules().socks_proxy);
  }
}

TEST(ProxyConfigTest, ToString) {
  // Manual proxy.
  {
    ProxyConfig config;
    config.set_auto_detect(false);
    config.proxy_rules().ParseFromString("http://single-proxy:81");

    EXPECT_EQ("Automatic settings:\n"
              "  Auto-detect: No\n"
              "  Custom PAC script: [None]\n"
              "Manual settings:\n"
              "  Proxy server: single-proxy:81\n"
              "  Bypass list: [None]",
              config.ToString());
  }

  // Autodetect + custom PAC + manual proxy.
  {
    ProxyConfig config;
    config.set_auto_detect(true);
    config.set_pac_url(GURL("http://custom/pac.js"));
    config.proxy_rules().ParseFromString("http://single-proxy:81");

    EXPECT_EQ("Automatic settings:\n"
              "  Auto-detect: Yes\n"
              "  Custom PAC script: http://custom/pac.js\n"
              "Manual settings:\n"
              "  Proxy server: single-proxy:81\n"
              "  Bypass list: [None]",
              config.ToString());
  }

  // Manual proxy with bypass list + bypass local.
  {
    ProxyConfig config;
    config.set_auto_detect(false);
    config.proxy_rules().ParseFromString("http://single-proxy:81");
    config.proxy_rules().bypass_rules.AddRuleFromString("google.com");
    config.proxy_rules().bypass_rules.AddRuleFromString("bypass2.net:1730");
    config.proxy_rules().bypass_rules.AddRuleToBypassLocal();

    EXPECT_EQ("Automatic settings:\n"
              "  Auto-detect: No\n"
              "  Custom PAC script: [None]\n"
              "Manual settings:\n"
              "  Proxy server: single-proxy:81\n"
              "  Bypass list: \n"
              "    google.com\n"
              "    bypass2.net:1730\n"
              "    <local>",
              config.ToString());
  }

  // Proxy-per scheme (HTTP and HTTPS)
  {
    ProxyConfig config;
    config.set_auto_detect(false);
    config.proxy_rules().ParseFromString(
        "http=proxy-for-http:1801; https=proxy-for-https:1802");

    EXPECT_EQ("Automatic settings:\n"
              "  Auto-detect: No\n"
              "  Custom PAC script: [None]\n"
              "Manual settings:\n"
              "  Proxy server: \n"
              "    HTTP: proxy-for-http:1801\n"
              "    HTTPS: proxy-for-https:1802\n"
              "  Bypass list: [None]",
              config.ToString());
  }

  // Proxy-per scheme (HTTP and SOCKS)
  {
    ProxyConfig config;
    config.set_auto_detect(false);
    config.proxy_rules().ParseFromString(
        "http=http://proxy-for-http:1801; socks=socks-server:6083");

    EXPECT_EQ("Automatic settings:\n"
              "  Auto-detect: No\n"
              "  Custom PAC script: [None]\n"
              "Manual settings:\n"
              "  Proxy server: \n"
              "    HTTP: proxy-for-http:1801\n"
              "    SOCKS: socks4://socks-server:6083\n"
              "  Bypass list: [None]",
              config.ToString());
  }

  // No proxy.
  {
    ProxyConfig config;
    config.set_auto_detect(false);

    EXPECT_EQ("Automatic settings:\n"
              "  Auto-detect: No\n"
              "  Custom PAC script: [None]\n"
              "Manual settings:\n"
              "  Proxy server: [None]\n"
              "  Bypass list: [None]",
              config.ToString());
  }

  // Manual proxy with bypass list + bypass local, list reversed.
  {
    ProxyConfig config;
    config.set_auto_detect(false);
    config.proxy_rules().ParseFromString("http://single-proxy:81");
    config.proxy_rules().bypass_rules.AddRuleFromString("google.com");
    config.proxy_rules().bypass_rules.AddRuleFromString("bypass2.net:1730");
    config.proxy_rules().bypass_rules.AddRuleToBypassLocal();
    config.proxy_rules().reverse_bypass = true;

    EXPECT_EQ("Automatic settings:\n"
              "  Auto-detect: No\n"
              "  Custom PAC script: [None]\n"
              "Manual settings:\n"
              "  Proxy server: single-proxy:81\n"
              "  Only use proxy for: \n"
              "    google.com\n"
              "    bypass2.net:1730\n"
              "    <local>",
              config.ToString());
  }
}

TEST(ProxyConfigTest, MayRequirePACResolver) {
  {
    ProxyConfig config;
    EXPECT_FALSE(config.MayRequirePACResolver());
  }
  {
    ProxyConfig config;
    config.set_auto_detect(true);
    EXPECT_TRUE(config.MayRequirePACResolver());
  }
  {
    ProxyConfig config;
    config.set_pac_url(GURL("http://custom/pac.js"));
    EXPECT_TRUE(config.MayRequirePACResolver());
  }
  {
    ProxyConfig config;
    config.set_pac_url(GURL("notvalid"));
    EXPECT_FALSE(config.MayRequirePACResolver());
  }
}

TEST(ProxyConfigTest, ReversedBypassList) {
  {
    ProxyConfig config;
    config.set_auto_detect(false);
    config.proxy_rules().ParseFromString("http://single-proxy:81");
    config.proxy_rules().bypass_rules.AddRuleFromString("google.com");
    config.proxy_rules().bypass_rules.AddRuleFromString("bypass2.net:1730");
    config.proxy_rules().bypass_rules.AddRuleToBypassLocal();
    config.proxy_rules().reverse_bypass = true;

    ProxyInfo info[3];
    GURL url0("http://google.com");
    GURL url1("http://www.webkit.com");
    GURL url2("http://bypass2.net:1730");

    config.proxy_rules().Apply(url0, &info[0]);
    EXPECT_EQ("single-proxy:81", info[0].proxy_server().ToURI());

    config.proxy_rules().Apply(url1, &info[1]);
    EXPECT_TRUE(info[1].is_direct());

    config.proxy_rules().Apply(url2, &info[2]);
    EXPECT_EQ("single-proxy:81", info[2].proxy_server().ToURI());
  }
}

}  // namespace
}  // namespace net

