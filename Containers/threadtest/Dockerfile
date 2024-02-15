FROM registry.access.redhat.com/ubi8:latest

ADD thread /

RUN \
    dnf install -y procps libstdc++ net-tools iproute && \
    echo "*     soft rtprio unlimited" >> /etc/security/limits.conf && \
    echo "*     hard rtprio unlimited" >> /etc/security/limits.conf

CMD [ "/thread" ]
