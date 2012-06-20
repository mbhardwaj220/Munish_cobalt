// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/dns/dns_config_service_win.h"

#include <algorithm>
#include <string>

#include "base/bind.h"
#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/file_path.h"
#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/metrics/histogram.h"
#include "base/string_split.h"
#include "base/string_util.h"
#include "base/synchronization/lock.h"
#include "base/threading/non_thread_safe.h"
#include "base/threading/thread_restrictions.h"
#include "base/time.h"
#include "base/utf_string_conversions.h"
#include "base/win/registry.h"
#include "base/win/windows_version.h"
#include "googleurl/src/url_canon.h"
#include "net/base/net_util.h"
#include "net/base/network_change_notifier.h"
#include "net/dns/dns_hosts.h"
#include "net/dns/dns_protocol.h"
#include "net/dns/serial_worker.h"

#pragma comment(lib, "iphlpapi.lib")

namespace net {

namespace internal {

namespace {

const wchar_t* const kPrimaryDnsSuffixPath =
    L"SOFTWARE\\Policies\\Microsoft\\System\\DNSClient";

enum HostsParseWinResult {
  HOSTS_PARSE_WIN_OK = 0,
  HOSTS_PARSE_WIN_UNREADABLE_HOSTS_FILE,
  HOSTS_PARSE_WIN_COMPUTER_NAME_FAILED,
  HOSTS_PARSE_WIN_IPHELPER_FAILED,
  HOSTS_PARSE_WIN_BAD_ADDRESS,
  HOSTS_PARSE_WIN_MAX  // Bounding values for enumeration.
};

// Convenience for reading values using RegKey.
class RegistryReader : public base::NonThreadSafe {
 public:
  explicit RegistryReader(const wchar_t* key) {
    // Ignoring the result. |key_.Valid()| will catch failures.
    key_.Open(HKEY_LOCAL_MACHINE, key, KEY_QUERY_VALUE);
  }

  bool ReadString(const wchar_t* name,
                  DnsSystemSettings::RegString* out) const {
    DCHECK(CalledOnValidThread());
    out->set = false;
    if (!key_.Valid()) {
      // Assume that if the |key_| is invalid then the key is missing.
      return true;
    }
    LONG result = key_.ReadValue(name, &out->value);
    if (result == ERROR_SUCCESS) {
      out->set = true;
      return true;
    }
    return (result == ERROR_FILE_NOT_FOUND);
  }

  bool ReadDword(const wchar_t* name,
                 DnsSystemSettings::RegDword* out) const {
    DCHECK(CalledOnValidThread());
    out->set = false;
    if (!key_.Valid()) {
      // Assume that if the |key_| is invalid then the key is missing.
      return true;
    }
    LONG result = key_.ReadValueDW(name, &out->value);
    if (result == ERROR_SUCCESS) {
      out->set = true;
      return true;
    }
    return (result == ERROR_FILE_NOT_FOUND);
  }

 private:
  base::win::RegKey key_;

  DISALLOW_COPY_AND_ASSIGN(RegistryReader);
};

// Wrapper for GetAdaptersAddresses. Returns NULL if failed.
scoped_ptr_malloc<IP_ADAPTER_ADDRESSES> ReadIpHelper(ULONG flags) {
  base::ThreadRestrictions::AssertIOAllowed();

  scoped_ptr_malloc<IP_ADAPTER_ADDRESSES> out;
  ULONG len = 15000;  // As recommended by MSDN for GetAdaptersAddresses.
  UINT rv = ERROR_BUFFER_OVERFLOW;
  // Try up to three times.
  for (unsigned tries = 0; (tries < 3) && (rv == ERROR_BUFFER_OVERFLOW);
       tries++) {
    out.reset(reinterpret_cast<PIP_ADAPTER_ADDRESSES>(malloc(len)));
    rv = GetAdaptersAddresses(AF_UNSPEC, flags, NULL, out.get(), &len);
  }
  if (rv != NO_ERROR)
    out.reset();
  return out.Pass();
}

// Converts a string16 domain name to ASCII, possibly using punycode.
// Returns true if the conversion succeeds and output is not empty. In case of
// failure, |domain| might become dirty.
bool ParseDomainASCII(const string16& widestr, std::string* domain) {
  DCHECK(domain);
  if (widestr.empty())
    return false;

  // Check if already ASCII.
  if (IsStringASCII(widestr)) {
    *domain = UTF16ToASCII(widestr);
    return true;
  }

  // Otherwise try to convert it from IDN to punycode.
  const int kInitialBufferSize = 256;
  url_canon::RawCanonOutputT<char16, kInitialBufferSize> punycode;
  if (!url_canon::IDNToASCII(widestr.data(), widestr.length(), &punycode))
    return false;

  // |punycode_output| should now be ASCII; convert it to a std::string.
  // (We could use UTF16ToASCII() instead, but that requires an extra string
  // copy. Since ASCII is a subset of UTF8 the following is equivalent).
  bool success = UTF16ToUTF8(punycode.data(), punycode.length(), domain);
  DCHECK(success);
  DCHECK(IsStringASCII(*domain));
  return success && !domain->empty();
}

bool ReadDevolutionSetting(const RegistryReader& reader,
                           DnsSystemSettings::DevolutionSetting* setting) {
  return reader.ReadDword(L"UseDomainNameDevolution", &setting->enabled) &&
         reader.ReadDword(L"DomainNameDevolutionLevel", &setting->level);
}

// Reads DnsSystemSettings from IpHelper and registry.
ConfigParseWinResult ReadSystemSettings(DnsSystemSettings* settings) {
  settings->addresses = ReadIpHelper(GAA_FLAG_SKIP_ANYCAST |
                                     GAA_FLAG_SKIP_UNICAST |
                                     GAA_FLAG_SKIP_MULTICAST |
                                     GAA_FLAG_SKIP_FRIENDLY_NAME);
  if (!settings->addresses.get())
    return CONFIG_PARSE_WIN_READ_IPHELPER;

  RegistryReader tcpip_reader(kTcpipPath);
  RegistryReader tcpip6_reader(kTcpip6Path);
  RegistryReader dnscache_reader(kDnscachePath);
  RegistryReader policy_reader(kPolicyPath);
  RegistryReader primary_dns_suffix_reader(kPrimaryDnsSuffixPath);

  if (!policy_reader.ReadString(L"SearchList",
                                &settings->policy_search_list)) {
    return CONFIG_PARSE_WIN_READ_POLICY_SEARCHLIST;
  }

  if (!tcpip_reader.ReadString(L"SearchList", &settings->tcpip_search_list))
    return CONFIG_PARSE_WIN_READ_TCPIP_SEARCHLIST;

  if (!tcpip_reader.ReadString(L"Domain", &settings->tcpip_domain))
    return CONFIG_PARSE_WIN_READ_DOMAIN;

  if (!ReadDevolutionSetting(policy_reader, &settings->policy_devolution))
    return CONFIG_PARSE_WIN_READ_POLICY_DEVOLUTION;

  if (!ReadDevolutionSetting(dnscache_reader, &settings->dnscache_devolution))
    return CONFIG_PARSE_WIN_READ_DNSCACHE_DEVOLUTION;

  if (!ReadDevolutionSetting(tcpip_reader, &settings->tcpip_devolution))
    return CONFIG_PARSE_WIN_READ_TCPIP_DEVOLUTION;

  if (!policy_reader.ReadDword(L"AppendToMultiLabelName",
                               &settings->append_to_multi_label_name)) {
    return CONFIG_PARSE_WIN_READ_APPEND_MULTILABEL;
  }

  if (!primary_dns_suffix_reader.ReadString(L"PrimaryDnsSuffix",
                                            &settings->primary_dns_suffix)) {
    return CONFIG_PARSE_WIN_READ_PRIMARY_SUFFIX;
  }
  return CONFIG_PARSE_WIN_OK;
}

// Default address of "localhost" and local computer name can be overridden
// by the HOSTS file, but if it's not there, then we need to fill it in.
HostsParseWinResult AddLocalhostEntries(DnsHosts* hosts) {
  const unsigned char kIPv4Localhost[] = { 127, 0, 0, 1 };
  const unsigned char kIPv6Localhost[] = { 0, 0, 0, 0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0, 0, 0, 1 };
  IPAddressNumber loopback_ipv4(kIPv4Localhost,
                                kIPv4Localhost + arraysize(kIPv4Localhost));
  IPAddressNumber loopback_ipv6(kIPv6Localhost,
                                kIPv6Localhost + arraysize(kIPv6Localhost));

  // This does not override any pre-existing entries from the HOSTS file.
  hosts->insert(std::make_pair(DnsHostsKey("localhost", ADDRESS_FAMILY_IPV4),
                               loopback_ipv4));
  hosts->insert(std::make_pair(DnsHostsKey("localhost", ADDRESS_FAMILY_IPV6),
                               loopback_ipv6));

  WCHAR buffer[MAX_PATH];
  DWORD size = MAX_PATH;
  std::string localname;
  if (!GetComputerNameExW(ComputerNameDnsHostname, buffer, &size) ||
      !ParseDomainASCII(buffer, &localname)) {
    return HOSTS_PARSE_WIN_COMPUTER_NAME_FAILED;
  }
  StringToLowerASCII(&localname);

  bool have_ipv4 =
      hosts->count(DnsHostsKey(localname, ADDRESS_FAMILY_IPV4)) > 0;
  bool have_ipv6 =
      hosts->count(DnsHostsKey(localname, ADDRESS_FAMILY_IPV6)) > 0;

  if (have_ipv4 && have_ipv6)
    return HOSTS_PARSE_WIN_OK;

  scoped_ptr_malloc<IP_ADAPTER_ADDRESSES> addresses =
      ReadIpHelper(GAA_FLAG_SKIP_ANYCAST |
                   GAA_FLAG_SKIP_DNS_SERVER |
                   GAA_FLAG_SKIP_MULTICAST |
                   GAA_FLAG_SKIP_FRIENDLY_NAME);
  if (!addresses.get())
    return HOSTS_PARSE_WIN_IPHELPER_FAILED;

  // The order of adapters is the network binding order, so stick to the
  // first good adapter for each family.
  for (const IP_ADAPTER_ADDRESSES* adapter = addresses.get();
       adapter != NULL && (!have_ipv4 || !have_ipv6);
       adapter = adapter->Next) {
    if (adapter->OperStatus != IfOperStatusUp)
      continue;
    if (adapter->IfType == IF_TYPE_SOFTWARE_LOOPBACK)
      continue;

    for (const IP_ADAPTER_UNICAST_ADDRESS* address =
             adapter->FirstUnicastAddress;
         address != NULL;
         address = address->Next) {
      IPEndPoint ipe;
      if (!ipe.FromSockAddr(address->Address.lpSockaddr,
                            address->Address.iSockaddrLength)) {
        return HOSTS_PARSE_WIN_BAD_ADDRESS;
      }
      if (!have_ipv4 && (ipe.GetFamily() == AF_INET)) {
        have_ipv4 = true;
        (*hosts)[DnsHostsKey(localname, ADDRESS_FAMILY_IPV4)] = ipe.address();
      } else if (!have_ipv6 && (ipe.GetFamily() == AF_INET6)) {
        have_ipv6 = true;
        (*hosts)[DnsHostsKey(localname, ADDRESS_FAMILY_IPV6)] = ipe.address();
      }
    }
  }
  return HOSTS_PARSE_WIN_OK;
}

}  // namespace

FilePath GetHostsPath() {
  TCHAR buffer[MAX_PATH];
  UINT rc = GetSystemDirectory(buffer, MAX_PATH);
  DCHECK(0 < rc && rc < MAX_PATH);
  return FilePath(buffer).Append(FILE_PATH_LITERAL("drivers\\etc\\hosts"));
}

bool ParseSearchList(const string16& value, std::vector<std::string>* output) {
  DCHECK(output);
  if (value.empty())
    return false;

  output->clear();

  // If the list includes an empty hostname (",," or ", ,"), it is terminated.
  // Although nslookup and network connection property tab ignore such
  // fragments ("a,b,,c" becomes ["a", "b", "c"]), our reference is getaddrinfo
  // (which sees ["a", "b"]). WMI queries also return a matching search list.
  std::vector<string16> woutput;
  base::SplitString(value, ',', &woutput);
  for (size_t i = 0; i < woutput.size(); ++i) {
    // Convert non-ASCII to punycode, although getaddrinfo does not properly
    // handle such suffixes.
    const string16& t = woutput[i];
    std::string parsed;
    if (!ParseDomainASCII(t, &parsed))
      break;
    output->push_back(parsed);
  }
  return !output->empty();
}

ConfigParseWinResult ConvertSettingsToDnsConfig(
    const DnsSystemSettings& settings,
    DnsConfig* config) {
  *config = DnsConfig();

  // Use GetAdapterAddresses to get effective DNS server order and
  // connection-specific DNS suffix. Ignore disconnected and loopback adapters.
  // The order of adapters is the network binding order, so stick to the
  // first good adapter.
  for (const IP_ADAPTER_ADDRESSES* adapter = settings.addresses.get();
       adapter != NULL && config->nameservers.empty();
       adapter = adapter->Next) {
    if (adapter->OperStatus != IfOperStatusUp)
      continue;
    if (adapter->IfType == IF_TYPE_SOFTWARE_LOOPBACK)
      continue;

    for (const IP_ADAPTER_DNS_SERVER_ADDRESS* address =
             adapter->FirstDnsServerAddress;
         address != NULL;
         address = address->Next) {
      IPEndPoint ipe;
      if (ipe.FromSockAddr(address->Address.lpSockaddr,
                           address->Address.iSockaddrLength)) {
        // Override unset port.
        if (!ipe.port())
          ipe = IPEndPoint(ipe.address(), dns_protocol::kDefaultPort);
        config->nameservers.push_back(ipe);
      } else {
        return CONFIG_PARSE_WIN_BAD_ADDRESS;
      }
    }

    // IP_ADAPTER_ADDRESSES in Vista+ has a search list at |FirstDnsSuffix|,
    // but it came up empty in all trials.
    // |DnsSuffix| stores the effective connection-specific suffix, which is
    // obtained via DHCP (regkey: Tcpip\Parameters\Interfaces\{XXX}\DhcpDomain)
    // or specified by the user (regkey: Tcpip\Parameters\Domain).
    std::string dns_suffix;
    if (ParseDomainASCII(adapter->DnsSuffix, &dns_suffix))
      config->search.push_back(dns_suffix);
  }

  if (config->nameservers.empty())
    return CONFIG_PARSE_WIN_NO_NAMESERVERS;  // No point continuing.

  // Windows always tries a multi-label name "as is" before using suffixes.
  config->ndots = 1;

  if (!settings.append_to_multi_label_name.set) {
    // The default setting is true for XP, false for Vista+.
    if (base::win::GetVersion() >= base::win::VERSION_VISTA) {
      config->append_to_multi_label_name = false;
    } else {
      config->append_to_multi_label_name = true;
    }
  } else {
    config->append_to_multi_label_name =
        (settings.append_to_multi_label_name.value != 0);
  }

  // SearchList takes precedence, so check it first.
  if (settings.policy_search_list.set) {
    std::vector<std::string> search;
    if (ParseSearchList(settings.policy_search_list.value, &search)) {
      config->search.swap(search);
      return CONFIG_PARSE_WIN_OK;
    }
    // Even if invalid, the policy disables the user-specified setting below.
  } else if (settings.tcpip_search_list.set) {
    std::vector<std::string> search;
    if (ParseSearchList(settings.tcpip_search_list.value, &search)) {
      config->search.swap(search);
      return CONFIG_PARSE_WIN_OK;
    }
  }

  // In absence of explicit search list, suffix search is:
  // [primary suffix, connection-specific suffix, devolution of primary suffix].
  // Primary suffix can be set by policy (primary_dns_suffix) or
  // user setting (tcpip_domain).
  //
  // The policy (primary_dns_suffix) can be edited via Group Policy Editor
  // (gpedit.msc) at Local Computer Policy => Computer Configuration
  // => Administrative Template => Network => DNS Client => Primary DNS Suffix.
  //
  // The user setting (tcpip_domain) can be configurred at Computer Name in
  // System Settings
  std::string primary_suffix;
  if ((settings.primary_dns_suffix.set &&
       ParseDomainASCII(settings.primary_dns_suffix.value, &primary_suffix)) ||
      (settings.tcpip_domain.set &&
       ParseDomainASCII(settings.tcpip_domain.value, &primary_suffix))) {
    // Primary suffix goes in front.
    config->search.insert(config->search.begin(), primary_suffix);
  } else {
    return CONFIG_PARSE_WIN_OK;  // No primary suffix, hence no devolution.
  }

  // Devolution is determined by precedence: policy > dnscache > tcpip.
  // |enabled|: UseDomainNameDevolution and |level|: DomainNameDevolutionLevel
  // are overridden independently.
  DnsSystemSettings::DevolutionSetting devolution = settings.policy_devolution;

  if (!devolution.enabled.set)
    devolution.enabled = settings.dnscache_devolution.enabled;
  if (!devolution.enabled.set)
    devolution.enabled = settings.tcpip_devolution.enabled;
  if (devolution.enabled.set && (devolution.enabled.value == 0))
    return CONFIG_PARSE_WIN_OK;  // Devolution disabled.

  // By default devolution is enabled.

  if (!devolution.level.set)
    devolution.level = settings.dnscache_devolution.level;
  if (!devolution.level.set)
    devolution.level = settings.tcpip_devolution.level;

  // After the recent update, Windows will try to determine a safe default
  // value by comparing the forest root domain (FRD) to the primary suffix.
  // See http://support.microsoft.com/kb/957579 for details.
  // For now, if the level is not set, we disable devolution, assuming that
  // we will fallback to the system getaddrinfo anyway. This might cause
  // performance loss for resolutions which depend on the system default
  // devolution setting.
  //
  // If the level is explicitly set below 2, devolution is disabled.
  if (!devolution.level.set || devolution.level.value < 2)
    return CONFIG_PARSE_WIN_OK;  // Devolution disabled.

  // Devolve the primary suffix. This naive logic matches the observed
  // behavior (see also ParseSearchList). If a suffix is not valid, it will be
  // discarded when the fully-qualified name is converted to DNS format.

  unsigned num_dots = std::count(primary_suffix.begin(),
                                 primary_suffix.end(), '.');

  for (size_t offset = 0; num_dots >= devolution.level.value; --num_dots) {
    offset = primary_suffix.find('.', offset + 1);
    config->search.push_back(primary_suffix.substr(offset + 1));
  }
  return CONFIG_PARSE_WIN_OK;
}

// Reads config from registry and IpHelper. All work performed on WorkerPool.
class DnsConfigServiceWin::ConfigReader : public SerialWorker {
 public:
  explicit ConfigReader(DnsConfigServiceWin* service)
      : service_(service),
        success_(false) {}

 private:
  virtual ~ConfigReader() {}

  virtual void DoWork() OVERRIDE {
    // Should be called on WorkerPool.
    base::TimeTicks start_time = base::TimeTicks::Now();
    DnsSystemSettings settings = {};
    ConfigParseWinResult result = ReadSystemSettings(&settings);
    if (result == CONFIG_PARSE_WIN_OK)
      result = ConvertSettingsToDnsConfig(settings, &dns_config_);
    success_ = (result == CONFIG_PARSE_WIN_OK);
    UMA_HISTOGRAM_ENUMERATION("AsyncDNS.ConfigParseWin",
                              result, CONFIG_PARSE_WIN_MAX);
    UMA_HISTOGRAM_BOOLEAN("AsyncDNS.ConfigParseResult", success_);
    UMA_HISTOGRAM_TIMES("AsyncDNS.ConfigParseDuration",
                        base::TimeTicks::Now() - start_time);
  }

  virtual void OnWorkFinished() OVERRIDE {
    DCHECK(loop()->BelongsToCurrentThread());
    DCHECK(!IsCancelled());
    if (success_) {
      service_->OnConfigRead(dns_config_);
    } else {
      LOG(WARNING) << "Failed to read DnsConfig.";
    }
  }

  DnsConfigServiceWin* service_;
  // Written in DoRead(), read in OnReadFinished(). No locking required.
  DnsConfig dns_config_;
  bool success_;
};

// Reads hosts from HOSTS file and fills in localhost and local computer name if
// necessary. All work performed on WorkerPool.
class DnsConfigServiceWin::HostsReader : public SerialWorker {
 public:
  explicit HostsReader(DnsConfigServiceWin* service)
      : path_(GetHostsPath()),
        service_(service),
        success_(false) {
  }

 private:
  virtual ~HostsReader() {}

  virtual void DoWork() OVERRIDE {
    base::TimeTicks start_time = base::TimeTicks::Now();
    HostsParseWinResult result = HOSTS_PARSE_WIN_UNREADABLE_HOSTS_FILE;
    if (ParseHostsFile(path_, &hosts_))
      result = AddLocalhostEntries(&hosts_);
    success_ = (result == HOSTS_PARSE_WIN_OK);
    UMA_HISTOGRAM_ENUMERATION("AsyncDNS.HostsParseWin",
                              result, HOSTS_PARSE_WIN_MAX);
    UMA_HISTOGRAM_BOOLEAN("AsyncDNS.HostParseResult", success_);
    UMA_HISTOGRAM_TIMES("AsyncDNS.HostsParseDuration",
                        base::TimeTicks::Now() - start_time);
  }

  virtual void OnWorkFinished() OVERRIDE {
    DCHECK(loop()->BelongsToCurrentThread());
    if (success_) {
      service_->OnHostsRead(hosts_);
    } else {
      LOG(WARNING) << "Failed to read DnsHosts.";
    }
  }

  const FilePath path_;
  DnsConfigServiceWin* service_;
  // Written in DoWork, read in OnWorkFinished, no locking necessary.
  DnsHosts hosts_;
  bool success_;

  DISALLOW_COPY_AND_ASSIGN(HostsReader);
};

DnsConfigServiceWin::DnsConfigServiceWin()
    : config_reader_(new ConfigReader(this)),
      hosts_reader_(new HostsReader(this)) {}

DnsConfigServiceWin::~DnsConfigServiceWin() {
  config_reader_->Cancel();
  hosts_reader_->Cancel();
  NetworkChangeNotifier::RemoveIPAddressObserver(this);
}

void DnsConfigServiceWin::Watch(const CallbackType& callback) {
  DnsConfigService::Watch(callback);
  // Also need to observe changes to local non-loopback IP for DnsHosts.
  NetworkChangeNotifier::AddIPAddressObserver(this);
}

void DnsConfigServiceWin::OnDNSChanged(unsigned detail) {
  if (detail & NetworkChangeNotifier::CHANGE_DNS_WATCH_FAILED) {
    InvalidateConfig();
    InvalidateHosts();
    // We don't trust a config that we cannot watch in the future.
    config_reader_->Cancel();
    hosts_reader_->Cancel();
    return;
  }
  if (detail & NetworkChangeNotifier::CHANGE_DNS_WATCH_STARTED)
    detail = ~0;  // Assume everything changed.
  if (detail & NetworkChangeNotifier::CHANGE_DNS_SETTINGS) {
    InvalidateConfig();
    config_reader_->WorkNow();
  }
  if (detail & NetworkChangeNotifier::CHANGE_DNS_HOSTS) {
    InvalidateHosts();
    hosts_reader_->WorkNow();
  }
}

void DnsConfigServiceWin::OnIPAddressChanged() {
  // Need to update non-loopback IP of local host.
  if (NetworkChangeNotifier::IsWatchingDNS())
    OnDNSChanged(NetworkChangeNotifier::CHANGE_DNS_HOSTS);
}

}  // namespace internal

// static
scoped_ptr<DnsConfigService> DnsConfigService::CreateSystemService() {
  return scoped_ptr<DnsConfigService>(new internal::DnsConfigServiceWin());
}

}  // namespace net

