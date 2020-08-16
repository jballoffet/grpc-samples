# Copyright 2017 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

licenses(["notice"])  # 3-clause BSD

package(default_visibility = ["//visibility:public"])

load("@com_github_grpc_grpc//bazel:grpc_build_system.bzl", "grpc_proto_library")

filegroup(
    name = "credentials_files",
    srcs = [
        "credentials/localhost.crt",
        "credentials/localhost.key",
        "credentials/root.crt",
    ],
)

grpc_proto_library(
    name = "helloworld_grpc",
    srcs = ["helloworld.proto"],
)

cc_binary(
    name = "greeter_client",
    srcs = [
        "helper.cc",
        "helper.h",
        "greeter_client.cc"
    ],
    data = [":credentials_files"],
    deps = [
        ":helloworld_grpc",
        "@com_github_grpc_grpc//:grpc++",
    ],
)

cc_binary(
    name = "greeter_server",
    srcs = [
        "helper.cc",
        "helper.h",
        "greeter_server.cc"
    ],
    data = [":credentials_files"],
    deps = [
        ":helloworld_grpc",
        "@com_github_grpc_grpc//:grpc++",
    ],
)
