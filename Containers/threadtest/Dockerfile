FROM fedora-minimal:34

ADD thread /

RUN \
    microdnf install -y procps libstdc++

CMD [ "/thread" ]