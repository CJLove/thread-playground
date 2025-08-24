#FROM registry.access.redhat.com/ubi8-minimal:8.10
FROM registry.access.redhat.com/ubi9-minimal:9.6

ADD thread /

RUN \
    microdnf install -y procps pam libstdc++ && \
    echo "*     soft rtprio unlimited" >> /etc/security/limits.conf && \
    echo "*     hard rtprio unlimited" >> /etc/security/limits.conf

CMD [ "/thread" ]
