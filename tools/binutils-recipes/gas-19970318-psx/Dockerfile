# The optional image override is for an already provisioned, recorded focal
# build environment. No source or Git retrieval occurs inside this build.
ARG BUILD_IMAGE=ubuntu@sha256:8feb4d8ca5354def3d8fce243717141ce31e2c428701f6682bd2fafe15388214
FROM ${BUILD_IMAGE} AS build
ENV DEBIAN_FRONTEND=noninteractive
RUN command -v gcc && command -v make && command -v bison && command -v flex \
    || (apt-get update && apt-get install -y --no-install-recommends build-essential gcc-multilib bison flex texinfo m4 patch perl)
WORKDIR /work
COPY binutils-2.8.tar.gz build.sh sanitize.sh /work/
COPY rollback /work/rollback
RUN sh /work/build.sh
FROM scratch AS export
COPY --from=build /build/as /as
