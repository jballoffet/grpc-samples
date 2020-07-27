# gRPC C++ sample apps

If you haven't built your docker image, just visit the [docker readme](../docker/README.md).

## Hello World sample app

### Building
To build the application, taking `{REPO_PATH}` as the base repository path, run the following:

```bash
cd `{REPO_PATH}`/workspace/helloworld
bazel build :greeter_server
bazel build :greeter_client
```

## Running
To run the application, taking `{REPO_PATH}` as the base repository path, run the following:

```bash
cd `{REPO_PATH}`/workspace/helloworld
bazel run :greeter_server
bazel run :greeter_client
```
