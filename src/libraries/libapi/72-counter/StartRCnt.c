#include "common.h"

/* D_000001E0: .data pointer initialized to MMIO 0x1F801070.
 * D_000001E8: per-counter enable-bit table {0x10, 0x20, 0x40, 0x100}.
 * Storage remains in _data.c; these declarations supply its source type. */
extern u32 *D_000001E0;
extern u32 D_000001E8[6];

s32 StartRCnt(s32 arg0) {
    s32 temp_v0;

    temp_v0 = arg0 & 0xFFFF;
    D_000001E0[1] |= D_000001E8[temp_v0];
    return temp_v0 < 3;
}
