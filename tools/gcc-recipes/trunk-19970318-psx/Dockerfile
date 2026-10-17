# GCC development trunk as of 1997-03-18 18:38 UTC (gcc-mirror commit 2b3600acb4ec),
# the last commit before the register-parameter REG_EQUIV change that the
# PSY-Q 4.7 library objects do not exhibit. See
# notes/research/compiler-identification-1997-trunk.md for the identification.
#
# The git history lacks the build scaffolding of that era (configure, version.c,
# obstack, the generated keyword table, getopt, stab headers, hash, tlink and the
# i386 Linux host headers). Those files are taken from the Cygnus 970404 tree
# (ser-pounce/cdk-gcc tag b18) and take no part in code generation. The parser
# is generated with byacc exactly as the Cygnus Makefile does.
FROM ubuntu:focal AS build
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates build-essential gcc gcc-multilib byacc patch wget

ENV TRUNK_COMMIT=2b3600acb4eceda3000312002ec78fecd5a39d30
ENV TRUNK_SHA256=a28c8f57d53c8a8196375ce82dcbfcabcb61547804f91169c242c577b52effa6
ENV CDK_SHA256=de4cba44576a4de3b6f750a5a3559fe9e91de1a75ccdf02d41bcf71f76114144

WORKDIR /work
RUN wget -q -O gcc-trunk-19970318.tar.gz https://codeload.github.com/gcc-mirror/gcc/tar.gz/${TRUNK_COMMIT} \
    && echo "${TRUNK_SHA256}  gcc-trunk-19970318.tar.gz" | sha256sum -c
RUN wget -q -O cdk-gcc-b18.tar.gz https://github.com/ser-pounce/cdk-gcc/archive/refs/tags/b18.tar.gz \
    && echo "${CDK_SHA256}  cdk-gcc-b18.tar.gz" | sha256sum -c
RUN tar xzf gcc-trunk-19970318.tar.gz && mv gcc-${TRUNK_COMMIT}/gcc gcc-trunk-19970318 && rm -rf gcc-${TRUNK_COMMIT}
RUN tar xzf cdk-gcc-b18.tar.gz

WORKDIR /work/gcc-trunk-19970318
COPY patches /work/patches
COPY byacc-wrap /work/byacc-wrap

# Build scaffolding absent from the git snapshot (no code-generation content).
RUN for f in configure version.c obstack.c obstack.h c-gperf.h getopt.c gstab.h stab.def hash.c hash.h tlink.c move-if-change gcov-io.h; do \
      cp -n /work/cdk-gcc-b18/$f . ; done \
    && cp -n /work/cdk-gcc-b18/config/xm-linux.h config/ \
    && cp -n /work/cdk-gcc-b18/config/i386/xm-linux.h config/i386/ \
    && for f in /work/cdk-gcc-b18/config/mips/xm-*.h; do cp -n $f config/mips/; done \
    && echo 'char *version_string = "trunk-19970318";' > version.c

# Modern-host build fixes and the little-endian default, as in decompals/old-gcc.
RUN patch -F3 -u -p1 obstack.h -i ../patches/obstack-2.7.2-cdk.h.patch \
    && patch -F3 -u -p1 config/mips/mips.h -i ../patches/mipsel-2.7-cdk.patch

RUN ./configure \
    --target=mips-linux-gnu \
    --prefix=/opt/cross \
    --with-endian-little \
    --with-gnu-as \
    --disable-gprof \
    --disable-gdb \
    --disable-werror \
    --host=i386-pc-linux \
    --build=i386-pc-linux

RUN make insn-config.h insn-flags.h insn-codes.h insn-attr.h BISON=/work/byacc-wrap CFLAGS="-std=gnu89 -m32 -static" \
    && make --jobs $(nproc) cc1 BISON=/work/byacc-wrap CFLAGS="-std=gnu89 -m32 -static"

COPY tests /work/tests
RUN ./cc1 -quiet -O2 -fno-exceptions /work/tests/little_endian.c && grep -E 'lbu\s\$2,0\(\$4\)' /work/tests/little_endian.s
RUN ./cc1 -quiet -O2 -fno-exceptions /work/tests/section_attribute.c
RUN ./cc1 -version -quiet -o /dev/null /work/tests/little_endian.c 2>&1 | grep 'trunk-19970318'

RUN mkdir -p /build && cp cc1 /build/

# Preserve the inputs and generated C/headers of this exact build, as the
# harness's own source capture does, so the source pin and binary correspond.
RUN set -eu; root=/work/gcc-trunk-19970318; dest=/build/compiler-source; \
    mkdir -p "$dest/src/gcc" "$dest/src/gcc/config"; \
    find "$root" -maxdepth 1 -type f \( -name '*.c' -o -name '*.h' -o -name '*.md' -o -name '*.def' -o -name '*.y' -o -name '*.in' -o -name '*.sh' -o -name '*.texi' -o -name 'Makefile*' -o -name 'configure*' -o -name 'config.*' -o -name 'COPYING*' -o -name 'ChangeLog*' -o -name 'README*' -o -name 'INSTALL*' \) -exec cp -p {} "$dest/src/gcc/" \; ; \
    find "$root/config" -maxdepth 1 -type f -exec cp -p {} "$dest/src/gcc/config/" \; ; \
    for arch in mips i386; do cp -a "$root/config/$arch" "$dest/src/gcc/config/"; done; \
    (cd /work && sha256sum gcc-trunk-19970318.tar.gz cdk-gcc-b18.tar.gz) > "$dest/upstream.sha256"

FROM scratch AS export
COPY --from=build /build/ .
