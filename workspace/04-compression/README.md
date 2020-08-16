# Compression sample app

## Building
To build the application, taking `{REPO_PATH}` as the base repository path, run the following:

```bash
cd `{REPO_PATH}`/workspace/04-compression
bazel build :greeter_server
bazel build :greeter_client
```

## Running
To run the application, taking `{REPO_PATH}` as the base repository path, run the following:

```bash
cd `{REPO_PATH}`/workspace/04-compression
bazel run :greeter_server
bazel run :greeter_client
```
