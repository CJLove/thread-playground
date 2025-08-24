# Staging directory for final image
ARG MICRODIR=/microdir
ARG PACKAGES_TO_INSTALL="libstdc++"

# ubi9-micro serves as the base for the final image
FROM registry.access.redhat.com/ubi9-micro:9.6 AS base

# ubi9 enables adding rpm dependencies and non-root user
FROM registry.access.redhat.com/ubi9:9.6 AS build
ARG MICRODIR
ARG PACKAGES_TO_INSTALL
RUN mkdir ${MICRODIR}
COPY --from=base / ${MICRODIR}
ADD thread ${MICRODIR}
RUN setcap 'cap_sys_nice=+eip' ${MICRODIR}/thread && \
    yum install \
  --installroot ${MICRODIR} \
  --releasever 8 \
  --setop install_weak_deps=false \
  -y \
  ${PACKAGES_TO_INSTALL}
RUN yum clean all \
  --installroot ${MICRODIR} && \
    groupadd -g 1000 testuser --prefix ${MICRODIR} && \
    useradd -u 1000 -g 1000 testuser --prefix ${MICRODIR}  

# Final image is built from scratch using the staging directory
FROM scratch AS image
ARG MICRODIR
COPY --from=build ${MICRODIR}/ .

USER testuser

CMD [ "/thread" ] 