/*
 *
 * Copyright 2015 gRPC authors.
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
    // Get the client's initial metadata.
    std::cout << "Client metadata: " << std::endl;
    const std::multimap<grpc::string_ref, grpc::string_ref> metadata = context->client_metadata();
    for (auto iter = metadata.begin(); iter != metadata.end(); ++iter) {
      std::cout << "Header key: " << iter->first << ", value: ";
      // Check for binary value.
      size_t isbin = iter->first.find("-bin");
      if ((isbin != std::string::npos) && (isbin + 4 == iter->first.size())) {
        std::cout <<  std::hex;
        for (auto c : iter->second) {
          std::cout << static_cast<unsigned int>(c);
        }
        std::cout <<  std::dec;
      } else {
        std::cout << iter->second;
      }
      std::cout << std::endl;
    }

    context->AddInitialMetadata("custom-server-metadata", "initial metadata value");
    context->AddTrailingMetadata("custom-trailing-metadata", "trailing metadata value");
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());
    return Status::OK;
  }
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  GreeterServiceImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}
