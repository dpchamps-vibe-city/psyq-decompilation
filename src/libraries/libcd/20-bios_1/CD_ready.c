INCLUDE_ASM("build/libraries/nonmatchings/libcd_20", CD_ready);


/* PARKED by /auto_decompilation_loop on 2026-10-20T05:37:03.051Z.
 * Reason: escalation-exhausted.
 * Escalation reached: deepseek-v4-1-flash-1017.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libcd_20::CD_ready.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"

extern volatile u8 *D_00001B3C;
extern volatile u8 D_00001B54[];
extern u8 B_00001B80[];
extern u8 B_00001B88[];
extern u8 B_00001B90[];
extern s32 B_00001B98 __asm__("$LB_00001B98");
extern s32 B_00001B9Crd __asm__("$LB_00001B98+4");
extern s32 B_00001B9Cwr __asm__("$LB_00001B9C");
extern char *B_00001BA0 __asm__("$LB_00001BA0");
extern u8 CD_com;
extern char *CD_comstr[];
extern char *CD_intstr[];
extern void (*CD_cbready)(u8, u8 *);
extern void (*CD_cbsync)(u8, u8 *);
extern char RO_STR_0000174C[] __asm__("$LRO_STR_0000174C");
extern char RO_STR_0000175C[] __asm__("$LRO_STR_0000175C");
extern char RO_STR_000017DC[] __asm__("$LRO_STR_000017DC");

extern s32 VSync(s32);
extern s32 CheckCallback(void);
extern s32 func_00000090(void);
extern void CD_flush(void);
extern int printf(const char *, ...);
extern int puts(const char *);

s32 CD_ready(s32 mode, u8 *result) {
    s32 i;
    s32 cnt;
    s32 old;
    s32 cb;
    s32 n;
    s32 ret;
    u8 intr;
    u8 *p;
    u8 *q;
    char **comstr;
    char **intstr;
    char *is0;

    B_00001B98 = VSync(-1) + 0x3C0;
    B_00001B9Cwr = 0;
    B_00001BA0 = RO_STR_000017DC;
    comstr = CD_comstr;
    intstr = CD_intstr;
    while (1) {
        if (B_00001B98 < VSync(-1) || (cnt = B_00001B9Crd, old = cnt, B_00001B9Cwr = ++cnt, old > 0x3C0000)) {
            puts(RO_STR_0000174C);
            i = D_00001B54[0];
            is0 = intstr[i];
            printf(RO_STR_0000175C, B_00001BA0, comstr[CD_com],
                   is0, intstr[D_00001B54[1]]);
            CD_flush();
            ret = -1;
        } else {
            ret = 0;
        }
        if (ret != 0) {
            return -1;
        }
        if (CheckCallback()) {
            intr = *D_00001B3C & 3;
            while ((cb = func_00000090()) != 0) {
                if (cb & 4) {
                    if (CD_cbready != 0) {
                        CD_cbready(D_00001B54[1], B_00001B88);
                    }
                }
                if ((cb & 2) && CD_cbsync != 0) {
                    CD_cbsync(D_00001B54[0], B_00001B80);
                }
            }
            *D_00001B3C = intr;
        }
        i = D_00001B54[2] & 0xFF;
        if (i != 0) {
            D_00001B54[2] = 0;
            p = B_00001B90;
            if (result != 0) {
                q = result;
                for (n = 7; n != -1; n--) {
                    *q++ = *p++;
                }
            }
            return i;
        }
        i = D_00001B54[1] & 0xFF;
        if (i != 0) {
            D_00001B54[1] = 0;
            q = result;
            p = B_00001B88;
            if (q != 0) {
                for (n = 7; n != -1; n--) {
                    *q++ = *p++;
                }
            }
            return i;
        }
        if (mode == 0) {
            continue;
        }
        return 0;
    }
}
#endif
