# gRPC C++ Samples

This repository contains some basic sample applications to start working with gRPC in C++, using Bazel as the build system. It also provides everything needed to run them in a docker container.

## Project organization

You'll find the following project organization:

- workspace: workspace directory.
  - helloworld: Hello World sample app.
- docker: docker related files.

## Installation

1. Clone this repository

```bash
git clone https://github.com/jballoffet/grpc-samples.git
```

2. Build docker image and run container, visit [docker readme](./docker/README.md)
for instructions.

3. Build and run the sample apps, visit [apps readme](./workspace/README.md) for instructions.

## Maintainers
This repository is mantained by:
* [Javier Balloffet](http://github.com/jballoffet)

## Original version
Samples apps are based on:
* [https://github.com/grpc/grpc/tree/master/examples/cpp](https://github.com/grpc/grpc/tree/master/examples/cpp)
