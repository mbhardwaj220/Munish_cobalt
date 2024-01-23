// Copyright 2015 The Cobalt Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// The basic Sunny Day test is a subset of other Sunny Day tests, so it is not
// repeated here.

#if SB_API_VERSION >= 16

#if defined(_WIN32)
#include <errno.h>
#include <io.h>
#include <winsock2.h>
#else
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

#include "starboard/common/socket.h"
#include "starboard/nplb/socket_helpers.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace starboard {
namespace nplb {
namespace {

class PosixSocketConnectTest : public ::testing::TestWithParam<int> {
 public:
  int GetAddressType() { return GetParam(); }
  int GetSocketDomain() { return GetParam() == 0 ? AF_INET : AF_INET6; }
};

TEST_P(PosixSocketConnectTest, RainyDayNullSocket) {
  sockaddr_in address = {};
  int a = GetAddressType();
  address.sin_family = GetSocketDomain();
  address.sin_port = 2048;

  int invalid_socket_fd = -1;
  EXPECT_FALSE(::connect(invalid_socket_fd,
                         reinterpret_cast<sockaddr*>(&address),
                         sizeof(sockaddr_in)) == 0);
}

TEST_P(PosixSocketConnectTest, RainyDayNullAddress) {
  int socket_domain, socket_type, socket_protocol;
  socket_domain = GetSocketDomain();
  socket_type = SOCK_STREAM;
  socket_protocol = IPPROTO_TCP;

  int socket_fd = ::socket(socket_domain, socket_type, socket_protocol);
  EXPECT_TRUE(socket_fd > 0);

  EXPECT_FALSE(connect(socket_fd, NULL, 0) == 0);

#if defined(_WIN32)
  EXPECT_TRUE(_close(socket_fd) == 0);
#else
  EXPECT_TRUE(close(socket_fd) == 0);
#endif
}

TEST(PosixSocketConnectTest, RainyDayNullNull) {
  int invalid_socket_fd = -1;

  EXPECT_FALSE(connect(invalid_socket_fd, NULL, 0) == 0);
}

}  // namespace
}  // namespace nplb
}  // namespace starboard
#endif  // SB_API_VERSION >= 16
