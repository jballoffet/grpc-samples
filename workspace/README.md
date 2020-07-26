# Sample app

## Building the app

If you haven't built your docker image, just visit the [docker readme](../docker/README.md).

To run the application, taking `{REPO_PATH}` as the base repository path, run the following:

```bash
cd {REPO_PATH}/workspace
mkdir build
cd build
cmake ..
make
./app
```
