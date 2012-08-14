// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_DNS_ADDRESS_SORTER_POSIX_H_
#define NET_DNS_ADDRESS_SORTER_POSIX_H_

#include <map>
#include <vector>

#include "base/threading/non_thread_safe.h"
#include "net/base/address_list.h"
#include "net/base/net_errors.h"
#include "net/base/net_export.h"
#include "net/base/net_util.h"
#include "net/base/network_change_notifier.h"
#include "net/dns/address_sorter.h"

namespace net {

class ClientSocketFactory;

// This implementation uses explicit policy to perform the sorting. It is not
// thread-safe and always completes synchronously.
class NET_EXPORT_PRIVATE AddressSorterPosix
    : public AddressSorter,
      public base::NonThreadSafe,
      public NetworkChangeNotifier::IPAddressObserver {
 public:
  // Generic policy entry.
  struct PolicyEntry {
    // IPv4 addresses must be mapped to IPv6.
    unsigned char prefix[kIPv6AddressSize];
    unsigned prefix_length;
    unsigned value;
  };

  typedef std::vector<PolicyEntry> PolicyTable;

  enum AddressScope {
    SCOPE_UNDEFINED = 0,
    SCOPE_NODELOCAL = 1,
    SCOPE_LINKLOCAL = 2,
    SCOPE_SITELOCAL = 5,
    SCOPE_ORGLOCAL = 8,
    SCOPE_GLOBAL = 14,
  };

  struct SourceAddressInfo {
    // Values read from policy tables.
    AddressScope scope;
    unsigned label;

    // Values from the OS, matter only if more than one source address is used.
    unsigned prefix_length;
    bool deprecated;  // vs. preferred RFC4862
    bool home;        // vs. care-of RFC6275
    bool native;
  };

  typedef std::map<IPAddressNumber, SourceAddressInfo> SourceAddressMap;

  explicit AddressSorterPosix(ClientSocketFactory* socket_factory);
  virtual ~AddressSorterPosix();

  // AddressSorter:
  virtual void Sort(const AddressList& list,
                    const CallbackType& callback) const OVERRIDE;

 private:
  friend class AddressSorterPosixTest;

  // NetworkChangeNotifier::IPAddressObserver:
  virtual void OnIPAddressChanged() OVERRIDE;

  // Fills |info| with values for |address| from policy tables.
  void FillPolicy(const IPAddressNumber& address,
                  SourceAddressInfo* info) const;

  // Mutable to allow using default values for source addresses which were not
  // found in most recent OnIPAddressChanged.
  mutable SourceAddressMap source_map_;

  ClientSocketFactory* socket_factory_;
  PolicyTable precedence_table_;
  PolicyTable label_table_;
  PolicyTable ipv4_scope_table_;

  DISALLOW_COPY_AND_ASSIGN(AddressSorterPosix);
};

}  // namespace net

#endif  // NET_DNS_ADDRESS_SORTER_POSIX_H_
