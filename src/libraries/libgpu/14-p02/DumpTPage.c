#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

extern char RO_STR_000000D0[];

void DumpTPage(u_short tpage) {
    u32 temp_a3;

    temp_a3 = tpage & 0xFFFF;
    GPU_printf(RO_STR_000000D0, (temp_a3 >> 7) & 3, (temp_a3 >> 5) & 3, (temp_a3 << 6) & 0x7C0, ((temp_a3 * 0x10) & 0x100) | ((temp_a3 >> 2) & 0x200));
}
