#!/bin/sh
# Build only the pinned PCSX-Redux LNK parser, not the emulator.
# All compilation outputs stay under build/. No SDK inputs are modified.
set -eu
ROOT=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
SOURCE="$ROOT/tools/pcsx-redux"
PIN=78e777e160d840c37b17872d864a8d896681d191
[ "$(git -C "$SOURCE" rev-parse HEAD)" = "$PIN" ] || {
    echo "Unexpected PCSX-Redux revision; review the pin before building." >&2
    exit 1
}
for dependency in ELFIO fmt magic_enum; do
    expected=$(git -C "$SOURCE" rev-parse "HEAD:third_party/$dependency")
    actual=$(git -C "$SOURCE/third_party/$dependency" rev-parse HEAD)
    [ "$actual" = "$expected" ] || {
        echo "Unexpected $dependency revision." >&2
        exit 1
    }
done
OUT="$ROOT/build/converters/pcsx-redux/$PIN"
mkdir -p "$OUT"
set -x
"${CXX:-g++}" -std=c++23 -O2 -pthread \
    -I"$SOURCE/src" -I"$SOURCE/third_party" \
    -I"$SOURCE/third_party/ELFIO" \
    -I"$SOURCE/third_party/fmt/include" \
    -I"$SOURCE/third_party/magic_enum/include" \
    "$SOURCE/tools/psyq-obj-parser/psyq-obj-parser.cc" \
    "$SOURCE/src/support/file.cc" \
    "$SOURCE/src/support/zfile.cc" \
    "$SOURCE/third_party/fmt/src/format.cc" \
    -lz -o "$OUT/psyq-obj-parser"
