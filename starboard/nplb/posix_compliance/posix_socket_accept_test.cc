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

// The accept SunnyDay case is tested as a subset of at least one other test
// case, so it is not included redundantly here.
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
#include "starboard/common/time.h"
#include "starboard/nplb/socket_helpers.h"
#include "starboard/shared/posix/handle_eintr.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace starboard {
namespace nplb {
namespace {

class PosixSocketAcceptTest : public ::testing::TestWithParam<int> {
 public:
  int GetAddressType() { return GetParam(); }
  int GetSocketDomain() { return GetParam() == 0 ? AF_INET : AF_INET6; }
};

TEST_P(PosixSocketAcceptTest, RainyDayInvalidSocket) {
  int invalid_socket_fd = -1;
  EXPECT_FALSE(::accept(invalid_socket_fd, NULL, NULL) == 0);
}

TEST_P(PosixSocketAcceptTest, RainyDayNoConnection) {
  // Set up a socket to listen.
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

  // bind
  struct sockaddr_in address = {0};
  address.sin_family = GetSocketDomain();
  address.sin_port = GetPortNumberForTests();
  return_value = ::bind(socket_fd, reinterpret_cast<sockaddr*>(&address),
                        sizeof(sockaddr_in));
  EXPECT_TRUE(return_value == 0);
  if (return_value < 0) {
#if defined(_WIN32)
    EXPECT_TRUE(_close(socket_fd) == 0);
#else
    EXPECT_TRUE(close(socket_fd) == 0);
#endif
    return;
  }

  // listen
#if defined(SOMAXCONN)
  const int kMaxConn = SOMAXCONN;
#else
  const int kMaxConn = 128;
#endif
  EXPECT_TRUE(::listen(socket_fd, kMaxConn) == 0);

  // Don't create a socket to connect to it.
  // Spin briefly to ensure that it won't accept.
  int64_t start = CurrentMonotonicTime();
  int accepted_socket_fd;
  while (true) {
    accepted_socket_fd = HANDLE_EINTR(accept(socket_fd, NULL, NULL));

    // If we didn't get a socket, it should be pending.
    EXPECT_TRUE(errno == EINPROGRESS || errno == EAGAIN
#if EWOULDBLOCK != EAGAIN
                || errno == EWOULDBLOCK
#endif
    );

    // Check if we have passed our timeout.
    if (CurrentMonotonicTime() - start >= kSocketTimeout) {
      break;
    }

    // Just being polite.
    SbThreadYield();
  }
#if defined(_WIN32)
  _close(accepted_socket_fd);
  EXPECT_TRUE(_close(socket_fd) == 0);
#else
  close(accepted_socket_fd);
  EXPECT_TRUE(close(socket_fd) == 0);
#endif
}

TEST_P(PosixSocketAcceptTest, RainyDayNotBound) {
  // Set up a socket, but don't Bind or Listen.
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

  // Accept should result in an error.
  EXPECT_FALSE(::accept(socket_fd, NULL, NULL) == 0);

  EXPECT_FALSE(errno == 0);

#if defined(_WIN32)
  EXPECT_TRUE(_close(socket_fd) == 0);
#else
  EXPECT_TRUE(close(socket_fd) == 0);
#endif
}

TEST_P(PosixSocketAcceptTest, RainyDayNotListening) {
  // Set up a socket, but don't Bind or Listen.
  int socket_domain, socket_type, socket_protocol;
  socket_domain = GetSocketDomain();
  socket_type = SOCK_STREAM;
  socket_protocol = IPPROTO_TCP;

  int socket_fd = ::socket(socket_domain, socket_type, socket_protocol);
  ASSERT_TRUE(socket_fd > 0);

  // Accept should result in an error.
  EXPECT_FALSE(::accept(socket_fd, NULL, NULL) == 0);

  EXPECT_FALSE(errno == 0);

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
