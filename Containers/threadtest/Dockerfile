# #FROM registry.access.redhat.com/ubi8-minimal:8.10
# FROM registry.access.redhat.com/ubi9-minimal:9.6

# ADD thread /

# RUN \
#     microdnf install -y libstdc++ 
# #    && \
# #    echo "*     soft rtprio unlimited" >> /etc/security/limits.conf && \
# #    echo "*     hard rtprio unlimited" >> /etc/security/limits.conf

# CMD [ "/thread" ]

# build using 

ARG MICRODIR=/microdir
ARG PACKAGES_TO_INSTALL="libstdc++"

FROM registry.access.redhat.com/ubi9-micro:9.6 AS base

FROM registry.access.redhat.com/ubi9:9.6 AS build
ARG MICRODIR
ARG PACKAGES_TO_INSTALL
RUN mkdir ${MICRODIR}
COPY --from=base / ${MICRODIR}
ADD thread ${MICRODIR}
RUN yum install \
  --installroot ${MICRODIR} \
  --releasever 8 \
  --setop install_weak_deps=false \
  -y \
  ${PACKAGES_TO_INSTALL}
RUN yum clean all \
  --installroot ${MICRODIR} && \
  groupadd -g 1000 testuser --prefix ${MICRODIR} && \
  useradd -u 1000 -g 1000 testuser --prefix ${MICRODIR}

FROM scratch AS image
ARG MICRODIR
COPY --from=build ${MICRODIR}/ .

USER testuser

CMD [ "/thread" ] 