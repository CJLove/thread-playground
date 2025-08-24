# thread-playground
Experimental code with C++ threads, real-time scheduling and containers

## Container image build

The threadtest container is built using multiple stages leveraging ubi9 for building and ubi9-micro as the base for the final image.

A non-root user is added, and the `cap_sys_nice` capability is applied to the executable during the container build process. Note that
with this capability added calls to `pthread_getname_np()` now failure with errno=EPERM.

## Container deployment

The `Containers/threadtest/threadtest.yaml` Kubernetes manifest deploys the pod with `cap_sys_nice` added but running as a non-root user.
