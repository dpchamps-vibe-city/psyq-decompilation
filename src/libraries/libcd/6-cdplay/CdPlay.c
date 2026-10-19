#include "common.h"
#include <sys/types.h>
#include <libcd.h>
#include <libetc.h>
#include <stdio.h>

extern s32 CD_debug;
extern char CdPlay_noToc[] __asm__("$LRO_STR_000005D8");
extern char CdPlay_dataend[] __asm__("$LRO_STR_00000600");
extern char CdPlay_error[] __asm__("$LRO_STR_0000062C");

static void func_000003EC(void) __asm__("$Lfunc_000003EC");
static void func_00000564(void) __asm__("$Lfunc_00000564");

extern s32 D_00000668 __asm__("$LD_00000668");
extern s32 D_0000066C[] __asm__("$LD_0000066C");
extern s32 D_000007FC __asm__("$LD_000007FC");
extern s32 D_00000800 __asm__("$LD_00000800");
extern s32 D_00000804 __asm__("$LD_00000804");
extern s32 D_00000808[] __asm__("$LD_00000808");
extern CdlLOC B_00000818[] __asm__("$LB_00000818");
extern s32 B_000009A8 __asm__("$LB_000009A8");
extern u_char B_000009B0[] __asm__("$LB_000009B0");

s32 CdPlay(s32 mode, s32 *track, s32 offset) {
    u_char param[8];
    u_char result[8];
    s32 i;

    if (mode == 3) {
        if (D_000007FC == -1) {
            return -1;
        }
        CdControl(1, 0, 0);
        if (CdSync(1, result) != 0) {
            if (!(result[0] & 0xC0)) {
                D_00000800 = 1;
            }
            if (D_00000800 == 0 || (result[0] & 0x10)) {
                CdControlF(1, 0);
                return D_000007FC;
            }
        } else {
            return D_000007FC;
        }
    } else if (mode == 0) {
        func_00000564();
        return D_000007FC;
    } else {
        if (!(B_000009A8 = CdGetToc(B_00000818))) {
            if (CD_debug >= 2) {
                printf(CdPlay_noToc);
            }
            D_000007FC = -1;
            return -1;
        }
        D_00000804 = mode != 1;
        for (i = 0; i < 99; i++) {
            if (track[i] == 0) {
                break;
            }
            D_0000066C[i] = track[i];
        }
        D_0000066C[i] = 0;
        D_000007FC = offset;
        if (offset >= 0) {
            if (i >= offset) {
                i = offset;
            }
        } else {
            i = 0;
        }
        D_000007FC = i;
        D_00000808[0] = D_0000066C[i];
        param[0] = 5;
        CdControl(0xE, param, 0);
    }
    func_000003EC();
    return D_000007FC;
}

#include "cdplay_private.h"
