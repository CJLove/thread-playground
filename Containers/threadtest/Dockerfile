FROM registry.access.redhat.com/ubi8-minimal:8.10

ADD thread /

RUN \
    microdnf install -y procps libstdc++ net-tools iproute && \
    echo "*     soft rtprio unlimited" >> /etc/security/limits.conf && \
    echo "*     hard rtprio unlimited" >> /etc/security/limits.conf

CMD [ "/thread" ]
