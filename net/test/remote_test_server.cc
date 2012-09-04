// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/test/remote_test_server.h"

#include <vector>

#include "base/base_paths.h"
#include "base/file_path.h"
#include "base/file_util.h"
#include "base/json/json_writer.h"
#include "base/logging.h"
#include "base/path_service.h"
#include "base/string_number_conversions.h"
#include "base/string_split.h"
#include "base/values.h"
#include "googleurl/src/gurl.h"
#include "net/base/host_port_pair.h"
#include "net/base/net_errors.h"
#include "net/test/spawner_communicator.h"

namespace net {

namespace {

// To reduce the running time of tests, tests may be sharded across several
// devices. This means that it may be necessary to support multiple instances
// of the test server spawner and the Python test server simultaneously on the
// same host. Each pair of (test server spawner, Python test server) correspond
// to a single testing device.
// The mapping between the test server spawner and the individual Python test
// servers is written to a file on the device prior to executing any tests.
FilePath GetTestServerPortInfoFile() {
#if !defined(OS_ANDROID)
  return FilePath("/tmp/net-test-server-ports");
#else
  FilePath test_data_dir;
  PathService::Get(base::DIR_ANDROID_EXTERNAL_STORAGE, &test_data_dir);
  test_data_dir.Append("net-test-server-ports");
  return test_data_dir;
#endif
}

// Please keep it sync with dictionary SERVER_TYPES in testserver.py
std::string GetServerTypeString(BaseTestServer::Type type) {
  switch (type) {
    case BaseTestServer::TYPE_FTP:
      return "ftp";
    case BaseTestServer::TYPE_GDATA:
    case BaseTestServer::TYPE_HTTP:
    case BaseTestServer::TYPE_HTTPS:
      return "http";
    case BaseTestServer::TYPE_SYNC:
      return "sync";
    case BaseTestServer::TYPE_TCP_ECHO:
      return "tcpecho";
    case BaseTestServer::TYPE_UDP_ECHO:
      return "udpecho";
    default:
      NOTREACHED();
  }
  return std::string();
}

}  // namespace

RemoteTestServer::RemoteTestServer(Type type,
                                   const std::string& host,
                                   const FilePath& document_root)
    : BaseTestServer(type, host),
      spawner_server_port_(0) {
  if (!Init(document_root))
    NOTREACHED();
}

RemoteTestServer::RemoteTestServer(Type type,
                                   const SSLOptions& ssl_options,
                                   const FilePath& document_root)
    : BaseTestServer(type, ssl_options),
      spawner_server_port_(0) {
  if (!Init(document_root))
    NOTREACHED();
}

RemoteTestServer::~RemoteTestServer() {
  Stop();
}

bool RemoteTestServer::Start() {
  if (spawner_communicator_.get())
    return true;
  spawner_communicator_.reset(new SpawnerCommunicator(spawner_server_port_));

  base::DictionaryValue arguments_dict;
  if (!GenerateArguments(&arguments_dict))
    return false;

  // Append the 'server-type' argument which is used by spawner server to
  // pass right server type to Python test server.
  arguments_dict.SetString("server-type", GetServerTypeString(type()));

  // Generate JSON-formatted argument string.
  std::string arguments_string;
  base::JSONWriter::Write(&arguments_dict, &arguments_string);
  if (arguments_string.empty())
    return false;

  // Start the Python test server on the remote machine.
  uint16 test_server_port;
  if (!spawner_communicator_->StartServer(arguments_string,
                                          &test_server_port)) {
    return false;
  }
  if (0 == test_server_port)
    return false;

  // Construct server data to initialize BaseTestServer::server_data_.
  base::DictionaryValue server_data_dict;
  // At this point, the test server should be spawned on the host. Update the
  // local port to real port of Python test server, which will be forwarded to
  // the remote server.
  server_data_dict.SetInteger("port", test_server_port);
  std::string server_data;
  base::JSONWriter::Write(&server_data_dict, &server_data);
  if (server_data.empty() || !ParseServerData(server_data)) {
    LOG(ERROR) << "Could not parse server_data: " << server_data;
    return false;
  }

  return SetupWhenServerStarted();
}

bool RemoteTestServer::Stop() {
  if (!spawner_communicator_.get())
    return true;
  CleanUpWhenStoppingServer();
  bool stopped = spawner_communicator_->StopServer();
  // Explicitly reset |spawner_communicator_| to avoid reusing the stopped one.
  spawner_communicator_.reset(NULL);
  return stopped;
}

bool RemoteTestServer::Init(const FilePath& document_root) {
  if (document_root.IsAbsolute())
    return false;

  // Gets ports information used by test server spawner and Python test server.
  int test_server_port = 0;

  // Parse file to extract the ports information.
  std::string port_info;
  if (!file_util::ReadFileToString(GetTestServerPortInfoFile(),
                                   &port_info) ||
      port_info.empty()) {
    return false;
  }

  std::vector<std::string> ports;
  base::SplitString(port_info, ':', &ports);
  if (ports.size() != 2u)
    return false;

  // Verify the ports information.
  base::StringToInt(ports[0], &spawner_server_port_);
  if (!spawner_server_port_ ||
      static_cast<uint32>(spawner_server_port_) >= kuint16max)
    return false;

  // Allow the test_server_port to be 0, which means the test server spawner
  // will pick up a random port to run the test server.
  base::StringToInt(ports[1], &test_server_port);
  if (static_cast<uint32>(test_server_port) >= kuint16max)
    return false;
  SetPort(test_server_port);

  SetResourcePath(document_root, FilePath().AppendASCII("net")
                                           .AppendASCII("data")
                                           .AppendASCII("ssl")
                                           .AppendASCII("certificates"));
  return true;
}

}  // namespace net

