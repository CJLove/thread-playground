# Containers with real-time threads

## Image
The `threadtest` directory holds a Dockerfile building an image running the `thread` app which starts 1 thread in SCHED_RR with priority 90, 1 thread in SCHED_FIFO with priority 50, and 1 thread in SCHED_OTHER.

## CentOS 7.9 w/Docker 
Docker needs to be configured with rt threads enabled by adding `--cpu-rt-runtime=950000` to the `ExecStart` line in `/usr/lib/systemd/system/docker.service` and restarting the Docker service.  This container can then be run with regular Docker adding the `SYS_NICE` capability:

```bash
$ docker run --rm -d --name threadtest --cap-add SYS_NICE --cpu-rt-runtime=820000 --cpu-rt-period=1000000 --security-opt seccomp=unconfined threadtest:latest
```

There should be no `Operation not permitted` errors in the logs for the threadtest container and running `chrt -p <pid>` for the `thread` process should show the following:

```bash
$ chrt -a -p 31477
pid 31477's current scheduling policy: SCHED_OTHER
pid 31477's current scheduling priority: 0
pid 31504's current scheduling policy: SCHED_RR
pid 31504's current scheduling priority: 90
pid 31505's current scheduling policy: SCHED_FIFO
pid 31505's current scheduling priority: 50
pid 31506's current scheduling policy: SCHED_OTHER
pid 31506's current scheduling priority: 0

$ ps -cT -p 31477
  PID  SPID CLS PRI TTY          TIME CMD
31477 31477 TS   19 ?        00:00:00 thread
31477 31504 RR  130 ?        00:00:00 MyRRThread
31477 31505 FF   90 ?        00:00:00 MyFIFOThread
31477 31506 TS   19 ?        00:00:00 MyOtherThread
```

## Container debugging
The `threadtestdebug` directory holds a Dockerfile for building an image running the `thread` app under `gdbserver`. It can be debugged using `gdb` from another host as follows:

```bash
$ gdb thread
(gdb) target remote localhost:2000
(gdb) c
```

This requires additiona parameters when starting the container: `-p 2000:2000 --cap-add=SYS_PTRACE`

## Podman (e.g. Fedora)

It seems like this container can be run rootless with Podman provided that the user's `ulimit -r` limit is `unlimited`.  This limit is set via `/etc/security/limits.conf`:

```
@love		hard	rtprio		 -1
@love		soft	rtprio		 -1
```

```bash
$ podman run --rm -d --name threadtest2 fir.love.io:3005/threadtest:latest
```

TBD: This container can be run as root 