#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

extern char RO_STR_000000B0[];

void DumpClut(u_short clut) {
    GPU_printf(RO_STR_000000B0, (clut & 0x3F) * 0x10, (u32) (clut & 0xFFFF) >> 6);
}
