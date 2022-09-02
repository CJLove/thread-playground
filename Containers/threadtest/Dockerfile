FROM centos:7

ADD thread /

RUN \
    yum install -y procps libstdc++ net-tools iproute && \
    echo "*     soft rtprio unlimited" >> /etc/security/limits.conf && \
    echo "*     hard rtprio unlimited" >> /etc/security/limits.conf

CMD [ "/thread" ]
