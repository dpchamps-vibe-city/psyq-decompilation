#!/bin/sh
# Build the trunk-19970318 compiler from its pinned upstream tarballs and install it
# into this project's runtime and source-pin locations (both git-ignored).
set -eu
here=$(cd "$(dirname "$0")" && pwd)
root=$(cd "$here/../../.." && pwd)
name=trunk-19970318-psx
mkdir -p "$root/build/compiler-provision"
out="$root/build/compiler-provision/$name"
rm -rf "$out"
docker build --file "$here/Dockerfile" --target export --output "type=local,dest=$out" "$here" > "$root/build/compiler-provision/$name.log" 2>&1
python3 "$here/install.py" "$out" "$@"
