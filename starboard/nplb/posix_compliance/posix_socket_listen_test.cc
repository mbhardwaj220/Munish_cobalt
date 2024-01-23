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

// SbSocketListen is Sunny Day tested in several other tests, so those won't be
// included here.

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

class PosixSocketListenTest : public ::testing::TestWithParam<int> {
 public:
  int GetAddressType() { return GetParam(); }
  int GetSocketDomain() { return GetParam() == 0 ? AF_INET : AF_INET6; }
};

TEST_F(PosixSocketListenTest, RainyDayInvalid) {
  int invalid_socket_fd = -1;
#if defined(SOMAXCONN)
  const int kMaxConn = SOMAXCONN;
#else
  // Some posix platforms such as FreeBSD do not define SOMAXCONN.
  // In this case, set the value to an arbitrary number large enough to
  // satisfy most use-cases and tests, empirically we have found that 128
  // is sufficient.  All implementations of listen() specify that a backlog
  // parameter larger than the system max will be silently truncated to the
  // system's max.
  const int kMaxConn = 128;
#endif
  EXPECT_FALSE(::listen(invalid_socket_fd, kMaxConn) == 0);
}

TEST_P(PosixSocketListenTest, SunnyDayUnbound) {
  int socket_domain, socket_type, socket_protocol;
  socket_domain = GetSocketDomain();
  socket_type = SOCK_STREAM;
  socket_protocol = IPPROTO_TCP;
  int socket_fd = ::socket(socket_domain, socket_type, socket_protocol);
  ASSERT_TRUE(socket_fd > 0);

  // Set reuse address to true
  const int on = 1;
  int return_value =
      setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  EXPECT_TRUE(return_value == 0);
  if (return_value != 0) {
#if defined(_WIN32)
    EXPECT_TRUE(_close(socket_fd) == 0);
#else
    EXPECT_TRUE(close(socket_fd) == 0);
#endif
    return;
  }

#if defined(SOMAXCONN)
  const int kMaxConn = SOMAXCONN;
#else
  const int kMaxConn = 128;
#endif
  EXPECT_TRUE(::listen(socket_fd, kMaxConn) == 0);

  // Listening on an unbound socket should listen to a system-assigned port on
  // all local interfaces.
  struct sockaddr_in address = {0};
  socklen_t socklen;
  return_value =
      getsockname(socket_fd, reinterpret_cast<sockaddr*>(&address), &socklen);
  if (return_value < 0) {
#if defined(_WIN32)
    EXPECT_TRUE(_close(socket_fd) == 0);
#else
    EXPECT_TRUE(close(socket_fd) == 0);
#endif
    return;
  }

  EXPECT_EQ(GetSocketDomain(), address.sin_family);
  EXPECT_NE(0, address.sin_port);

#if defined(_WIN32)
  EXPECT_TRUE(_close(socket_fd) == 0);
#else
  EXPECT_TRUE(close(socket_fd) == 0);
#endif
}

}  // namespace
}  // namespace nplb
}  // namespace starboard
#endif  // SB_API_VERSION >= 16
