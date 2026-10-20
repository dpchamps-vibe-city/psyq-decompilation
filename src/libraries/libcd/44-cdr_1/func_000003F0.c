INCLUDE_ASM("build/libraries/nonmatchings/libcd_44", func_000003F0);


/* PARKED by /auto_decompilation_loop on 2026-10-20T16:51:24.833Z.
 * Reason: escalation-exhausted.
 * Escalation reached: deepseek-v4-1-flash-1017.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libcd_44::func_000003F0.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <sys/types.h>
#include <libcd.h>
#include <libetc.h>
#include <stdio.h>

extern s32 CD_read_dma_mode;
extern volatile CdReadState cd __asm__("$LD_00000A68");
extern char CdRead_shell_open[] __asm__("$LRO_STR_00000A18+24");
extern char CdRead_retry[] __asm__("$LRO_STR_00000A18+48");

int func_000003F0(s32 arg0) __asm__("$Lfunc_000003F0");

int func_000003F0(s32 arg0) {
    u8 sp10;
    s32 temp_s0;

    CdSyncCallback(0);
    CdReadyCallback(0);
    if (CD_read_dma_mode & 1) {
        CdDataCallback(0);
    }
    if (CdStatus() & 0x10) {
        if ((VSync(-1) & 0x3F) == 0) {
            puts(CdRead_shell_open);
        }
        CdControlF(1, 0);
        cd.unk1C = VSync(-1);
        cd.unk14 = -1;
        return cd.unk14;
    }
    if (((arg0 != 0) && (puts(CdRead_retry), CdControl(9, 0, 0),
                          (CdControl(2, (u_char *)CdLastPos(), 0) == 0))) ||
        (((CdFlush(), temp_s0 = cd.unkC), sp10 = temp_s0,
          ((temp_s0 & 0xFF) != CdMode())) || (arg0 != 0)) &&
         (CdControl(0xE, &sp10, 0) == 0)) {
        cd.unk14 = -1;
        return cd.unk14;
    }
    cd.unk20 = CdPosToInt(CdLastPos());
    CdReadyCallback(func_000000AC);
    if (CD_read_dma_mode & 1) {
        CdDataCallback(func_00000320);
    }
    cd.unk8 = cd.unk4;
    CdControlF(6, 0);
    cd.unk14 = cd.unk0;
    cd.unk18 = VSync(-1);
    return cd.unk14;
}
#endif
