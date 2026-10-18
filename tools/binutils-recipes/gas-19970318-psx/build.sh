#!/bin/sh
# Official release + checked rollback; no candidate-object corrections.
set -eu
work=${WORK:-/work}
echo '803733c8f748268875bfea542a55fa7cad24be9fb390d4584939f8122be97379  binutils-2.8.tar.gz' | (cd "$work" && sha256sum -c -)
(cd "$work/rollback" && sha256sum -c patches.sha256)
# Keep the source/build paths constant: GCC embeds assertion file names.
src="$work/src-hpin-mipsel-ecoff"
rm -rf "$src"; mkdir -p "$src" /build
tar -xf "$work/binutils-2.8.tar.gz" -C "$src" --strip-components=1
sh "$work/sanitize.sh" "$src/gas" "$src/bfd" "$src/opcodes" "$src/include"
for patch in "$work"/rollback/*.patch; do (cd "$src" && patch --batch --fuzz=0 -p1 < "$patch"); done
(cd "$src" && sha256sum -c "$work/rollback/result.sha256")
# Only host fix: modern glibc owns these declarations. No gas/bfd/opcodes fix.
for f in strerror strsignal; do
  sed -i '/#include "config.h"/a #undef NEED_sys_errlist\n#undef NEED_sys_siglist' "$src/libiberty/$f.c"
done
mkdir "$src/build"; cd "$src/build"
CC='gcc -m32 -std=gnu89 -fcommon -w -DANSI_PROTOTYPES' ../configure \
  --host=i386-pc-linux --build=i386-pc-linux --target=mipsel-ecoff --disable-nls
make all-gas CC='gcc -m32 -std=gnu89 -fcommon -w -DANSI_PROTOTYPES' CFLAGS=-O2 LDFLAGS=-static
cp gas/as.new /build/as
sha256sum /build/as
