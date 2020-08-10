# Route Guide sample app

## Building
To build the application, taking `{REPO_PATH}` as the base repository path, run the following:

```bash
cd `{REPO_PATH}`/workspace/3-route_guide
bazel build :route_guide_server
bazel build :route_guide_client
```

## Running
To run the application, taking `{REPO_PATH}` as the base repository path, run the following:

```bash
cd `{REPO_PATH}`/workspace/3-route_guide
bazel run :route_guide_server
bazel run :route_guide_client
```
