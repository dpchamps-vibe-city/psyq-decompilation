#include "common.h"
#include <libcd.h>

static s32 func_00000974(s32, s32, u8 *) __asm__("$Lfunc_00000974");

static s32 func_00000974(s32 arg0, s32 arg1, u8 *arg2) {
    CdlLOC sp10;

    CdIntToPos(arg1, &sp10);
    CdControl(2, (u_char *)&sp10, 0);
    CdRead(arg0, (u_long *)arg2, 0x80);
    return CdReadSync(0, 0) == 0;
}
