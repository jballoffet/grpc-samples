/*
 *
 * Copyright 2018 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "helper.h"
#include "helloworld.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;

class GreeterServiceImpl final : public Greeter::Service {
  Status SayHello(ServerContext* context, const HelloRequest* request,
                  HelloReply* reply) override {
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());
    return Status::OK;
  }
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  GreeterServiceImpl service;

  // Load credentials.
  std::string root = authentication::GetCredentialFileContent("credentials/root.crt");
  std::string key = authentication::GetCredentialFileContent("credentials/localhost.key");
  std::string cert = authentication::GetCredentialFileContent("credentials/localhost.crt");

  // Set SSL credentials.
  grpc::SslServerCredentialsOptions::PemKeyCertPair key_cert = {key, cert};
  grpc::SslServerCredentialsOptions ssl_opts;
  ssl_opts.pem_root_certs = root;
  ssl_opts.pem_key_cert_pairs.push_back(key_cert);

  // Build server.
  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::SslServerCredentials(ssl_opts));
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}