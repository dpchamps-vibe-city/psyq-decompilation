#!/bin/sh
# Offline provisioning from a supplied, checksum-verified public release.
set -eu
here=$(cd "$(dirname "$0")" && pwd)
root=$(cd "$here/../../.." && pwd)
archive=${BINUTILS_ARCHIVE:-$root/build/assembler-provenance/binutils/tarballs/binutils-2.8.tar.gz}
image=${BUILD_IMAGE:-ubuntu:focal}
# Never pull implicitly. Build the Dockerfile's focal environment separately
# when it is unavailable; this command only consumes installed local inputs.
BUILD_IMAGE=$(docker image inspect "$image" --format '{{.Id}}')
export BUILD_IMAGE
out="$root/build/assembler-provision/gas-19970318-psx"
mkdir -p "$out"
context=$(mktemp -d "$out/context.XXXXXX")
trap 'rm -rf "$context"' EXIT HUP INT TERM
cp "$archive" "$context/binutils-2.8.tar.gz"
cp "$here/build.sh" "$here/sanitize.sh" "$context/"
cp -R "$here/rollback" "$context/rollback"
docker run --pull=never --rm --network=none -v "$context:/work" -v "$out:/build" "$BUILD_IMAGE" sh /work/build.sh > "$out/build.log" 2>&1
node --import tsx "$here/tests/check.ts" "$out/as"
node --import tsx "$here/install.ts" "$out" "$@"
