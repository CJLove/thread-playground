FROM centos/devtoolset-7-toolchain-centos7:latest

ADD thread /

USER 0

RUN \
    yum install -y devtoolset-7-gdb-gdbserver

EXPOSE 2000
CMD gdbserver :2000 "/thread"
