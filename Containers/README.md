# Containers with real-time threads

## Image
The `threadtest` directory holds a Dockerfile building an image running the `thread` app which starts 1 thread in SCHED_RR with priority 2, 1 thread in SCHED_FIFO with priority 1, and 1 thread in SCHED_OTHER.

## Docker (e.g. non-Fedora)

This container can be run with regular Docker adding the `SYS_NICE` capability:

```bash
$ sudo docker run --rm -d --name threadtest --cap-add SYS_NICE fir.love.io:3005/threadtest:latest
```

## Podman (e.g. Fedora)

It seems like this container can be run rootless with Podman provided that the user's `ulimit -r` limit is `unlimited`.  This limit is set via `/etc/security/limits.conf`:

```bash
$ podman run --rm -d --name threadtest2 fir.love.io:3005/threadtest:latest
```

TBD: This container can be run as root 