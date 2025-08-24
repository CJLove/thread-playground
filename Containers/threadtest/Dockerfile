# #FROM registry.access.redhat.com/ubi8-minimal:8.10
# FROM registry.access.redhat.com/ubi9-minimal:9.6

# ADD thread /

# RUN \
#     microdnf install -y libstdc++ 
# #    && \
# #    echo "*     soft rtprio unlimited" >> /etc/security/limits.conf && \
# #    echo "*     hard rtprio unlimited" >> /etc/security/limits.conf

# CMD [ "/thread" ]

# Build using 

ARG MICRODIR=/microdir
ARG PACKAGES_TO_INSTALL="libstd-c++"

FROM registry.access.redhat.com/ubi9-micro:9.6 AS BASE

FROM registry.access.redhat.com/ubi9:9.6 AS BUILD
ARG MICRODIR
ARG PACKAGES_TO_INSTALL
RUN mkdir ${MICRODIR}
COPY --from=BASE / ${MICRODIR}
ADD thread ${MICRODIR}
RUN yum install \
  --installroot ${MICRODIR} \
  --releasever 8 \
  --setop install_weak_deps=false \
  -y \
  ${PACKAGES_TO_INSTALL}
RUN yum clean all \
  --installroot ${MICRODIR}

FROM scratch AS IMAGE
ARG MICRODIR
COPY --from=BUILD ${MICRODIR}/ .

CMD [ "/thread" ] 