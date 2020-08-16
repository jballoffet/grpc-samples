# Key-Value Store sample app

## Building
To build the application, taking `{REPO_PATH}` as the base repository path, run the following:

```bash
cd `{REPO_PATH}`/workspace/09-keyvalue_store
bazel build :keyvalue_store_server
bazel build :keyvalue_store_client
```

## Running
To run the application, taking `{REPO_PATH}` as the base repository path, run the following:

```bash
cd `{REPO_PATH}`/workspace/09-keyvalue_store
bazel run :keyvalue_store_server
bazel run :keyvalue_store_client
```
