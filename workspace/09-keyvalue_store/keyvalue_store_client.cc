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
#include <vector>

#include <grpcpp/grpcpp.h>

#include "caching_interceptor.h"

#include "keyvalue_store.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using keyvalue_store::KeyValueStore;
using keyvalue_store::Request;
using keyvalue_store::Response;

class KeyValueStoreClient {
 public:
  KeyValueStoreClient(std::shared_ptr<Channel> channel)
      : stub_(KeyValueStore::NewStub(channel)) {}

  // Requests each key in the vector and displays the key and its corresponding
  // value as a pair.
  void GetValues(const std::vector<std::string>& keys) {
    ClientContext context;
    auto stream = stub_->GetValues(&context);
    for (const auto& key : keys) {
      // Key we are sending to the server.
      Request request;
      request.set_key(key);
      stream->Write(request);

      // Get the value for the sent key.
      Response response;
      stream->Read(&response);
      std::cout << key << " : " << response.value() << "\n";
    }
    stream->WritesDone();
    Status status = stream->Finish();
    if (!status.ok()) {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      std::cout << "RPC failed";
    }
  }

 private:
  std::unique_ptr<KeyValueStore::Stub> stub_;
};

int main(int argc, char** argv) {
  // Use a cache which has been added in as an interceptor.
  grpc::ChannelArguments args;
  std::vector<
      std::unique_ptr<grpc::experimental::ClientInterceptorFactoryInterface>>
      interceptor_creators;
  interceptor_creators.push_back(std::unique_ptr<CachingInterceptorFactory>(
      new CachingInterceptorFactory()));

  KeyValueStoreClient client(grpc::experimental::CreateCustomChannelWithInterceptors(
      "localhost:50051", grpc::InsecureChannelCredentials(), args,
      std::move(interceptor_creators)));

  std::vector<std::string> keys = {"key1", "key2", "key3", "key4",
                                   "key5", "key1", "key2", "key4"};
  client.GetValues(keys);

  return 0;
}
