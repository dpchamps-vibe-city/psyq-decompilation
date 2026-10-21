INCLUDE_ASM("build/libraries/nonmatchings/libcd_16", func_000009C0);


/* PARKED by /auto_decompilation_loop on 2026-10-20T00:22:27.394Z.
 * Reason: escalation-exhausted.
 * Escalation reached: deepseek-v4-1-flash-1017.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libcd_16::func_000009C0.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"

extern volatile u8 *LD_00000B88 asm("D_00000B88");
extern volatile u32 *LD_00000BA0 asm("D_00000BA0");
extern volatile u32 *LD_00000BA4 asm("D_00000BA4");
extern int printf(const char *, ...);

void func_000009C0(s32 arg0, void *arg1, s32 arg2, s32 arg3, u32 arg4, s32 arg5, s32 arg6) {
    volatile u32 *p;
    volatile u32 dummy;
    s32 i;
    s32 flag;
    u8 val;
    volatile u8 *q;
    s32 limit;

    flag = (u8)arg5;
    limit = 0x10000;
    i = 0;
    while (*(volatile u32 *)(0x1F801088 + (arg0 << 4)) & 0x01000000) {
        if (i == limit) {
            printf("DMA STATUS ERROR %x\n", *(volatile u32 *)(0x1F801088 + (arg0 << 4)));
            break;
        }
        i++;
    }
    if (flag == 1) {
        q = (volatile u8 *)LD_00000BA4;
        val = q[2] | (1 << arg0);
    } else {
        q = (volatile u8 *)LD_00000BA4;
        val = q[2] & ~(1 << arg0);
    }
    q[2] = val;
    dummy = LD_00000BA4[0];
    *(u32 *)LD_00000BA0 |= 1 << ((arg0 << 2) + 3);
    p = (volatile u32 *)(0x1F801080 + (arg0 << 4));
    *p++ = (u32)arg1;
    *p++ = ((u32)arg2 << 16) | (u32)arg3;
    while (!(*LD_00000B88 & 0x40)) {
    }
    *p = arg4;
    dummy = *p;
}
#endif
