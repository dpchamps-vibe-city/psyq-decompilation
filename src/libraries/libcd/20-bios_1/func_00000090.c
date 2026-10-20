INCLUDE_ASM("build/libraries/nonmatchings/libcd_20", func_00000090);


/* PARKED by autoloop on 2026-10-20.
 * Reason: blocked (capability: harness part model cannot split generated data).
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Human decision needed: notes/human-needed-approvals/libcd_20::func_00000090.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session.
 * build/candidates/func_00000090/exp7-computed-goto.c  — 305/345 words
 * (all dbr/mach/greg/lreg stages agree; the 40 residual words are exactly +0x20
 *  on .data/.bss lo16 immediates — pure section-placement gap, not a semantic miss).
 * A switch-based variant (build/candidates/func_00000090/exp6-tidy.c, 303/345)
 * gives the same residual shape.
 */

#include "common.h"

extern volatile u8 *LD_00001B3C asm("$LD_00001B3C");
extern volatile u8 *LD_00001B40 asm("$LD_00001B40");
extern volatile u8 *LD_00001B48 asm("$LD_00001B48");
extern volatile u8 *LD_00001B4C asm("$LD_00001B4C");
extern volatile u8 B_00001B54[] asm("$LD_00001B54");
extern u8 B_00001B80[] asm("$LB_00001B80");
extern u8 B_00001B88[] asm("$LB_00001B88");
extern u8 B_00001B90[] asm("$LB_00001B90");
extern u32 D_0000193C[] asm("$LD_0000193C");
extern u32 D_00001A3C[] asm("$LD_00001A3C");

extern u8 CD_com;
extern s32 CD_status;
extern s32 CD_status1;
extern s32 CD_nopen;
extern s32 CD_debug;
extern char *CD_comstr[];

extern void *JT_000017C0[] asm("$LRO_STR_00001610");

#define CGOTO(p) goto *(p)

extern char CD_str_disk[] asm("$LRO_STR_00001778");
extern char CD_str_com[] asm("$LRO_STR_00001784");
extern char CD_str_unknown[] asm("$LRO_STR_000017A0");
extern char CD_str_pct[] asm("$LRO_STR_000017B4");

extern int printf(const char *, ...);
extern int puts(const char *);

s32 func_00000090(void) {
    volatile u8 intr;
    volatile u8 buf[8];
    u8 *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8, *p9;
    u8 *q1, *q2, *q3, *q4, *q5, *q6, *q7, *q8, *q9;
    s32 i;
    s32 n;
    s32 idx;
    s32 n1, n2, n3, n4, n5, n6, n7, n8, n9;
    s32 stat;
    s32 c;

    static void *const keep[] = { &&L3, &&L2, &&L1, &&L4, &&L5 };

    *LD_00001B3C = 1;
    intr = *LD_00001B40 & 7;
    if (intr == 0) {
        return 0;
    }
    stat = 0;
    while (intr != (*LD_00001B40 & 7)) {
        intr = *LD_00001B40 & 7;
    }
    for (i = 0; i < 8; i++) {
        if (!(*LD_00001B3C & 0x20)) {
            break;
        }
        buf[i] = *LD_00001B48;
    }
    if (i < 8) {
        for (n = i; n < 8; n++) {
            buf[n] = 0;
        }
    }
    *LD_00001B3C = 1;
    *LD_00001B40 = 7;
    *LD_00001B4C = 7;

    if ((intr != 3) || (D_00001A3C[CD_com] != 0)) {
        if (!(CD_status & 0x10) && (buf[0] & 0x10)) {
            CD_nopen++;
        }
        c = buf[0];
        stat = c & 0x1D;
        CD_status = c & 0xFF;
        CD_status1 = buf[1];
    }

    if (intr == 5) {
        if (CD_debug >= 3) {
            printf(CD_str_disk);
            if (CD_debug >= 3) {
                printf(CD_str_com, CD_comstr[CD_com], CD_status, CD_status1);
            }
        }
    }

    idx = intr - 1;
    if ((u32)idx < 5u) {
        CGOTO(JT_000017C0[idx + 108]);
    }
    goto Ldef;

L3:
        if (stat != 0) {
            B_00001B54[0] = 5;
            p1 = B_00001B80;
            if (p1 != 0) {
                q1 = buf;
                for (n1 = 7; n1 != -1; n1--) {
                    *p1++ = *q1++;
                }
            }
            return 2;
        }
        if (D_0000193C[CD_com] != 0) {
            B_00001B54[0] = 3;
            p2 = B_00001B80;
            if (p2 != 0) {
                q2 = buf;
                for (n2 = 7; n2 != -1; n2--) {
                    *p2++ = *q2++;
                }
            }
            return 1;
        }
        B_00001B54[0] = 2;
        p3 = B_00001B80;
        if (p3 != 0) {
            q3 = buf;
            for (n3 = 7; n3 != -1; n3--) {
                *p3++ = *q3++;
            }
        }
        return 2;
L2:
        B_00001B54[0] = stat ? 5 : 2;
        p4 = B_00001B80;
        if (p4 != 0) {
            q4 = buf;
            for (n4 = 7; n4 != -1; n4--) {
                *p4++ = *q4++;
            }
        }
        return 2;
L1:
        if (stat != 0 && i == 1) {
            stat = 0;
        }
        B_00001B54[1] = stat ? 5 : 1;
        p5 = B_00001B88;
        if (p5 != 0) {
            q5 = buf;
            for (n5 = 7; n5 != -1; n5--) {
                *p5++ = *q5++;
            }
        }
        *LD_00001B3C = 0;
        *LD_00001B40 = 0;
        return 4;
L4:
        p6 = B_00001B90;
        B_00001B54[2] = 4;
        B_00001B54[1] = B_00001B54[2];
        q6 = buf;
        if (p6 != 0) {
            for (n6 = 7; n6 != -1; n6--) {
                *p6++ = *q6++;
            }
        }
        p7 = B_00001B88;
        if (p7 != 0) {
            q7 = buf;
            for (n7 = 7; n7 != -1; n7--) {
                *p7++ = *q7++;
            }
        }
        return 4;
L5:
        p8 = B_00001B80;
        B_00001B54[1] = 5;
        B_00001B54[0] = B_00001B54[1];
        q8 = buf;
        if (p8 != 0) {
            for (n8 = 7; n8 != -1; n8--) {
                *p8++ = *q8++;
            }
        }
        p9 = B_00001B88;
        if (p9 != 0) {
            q9 = buf;
            for (n9 = 7; n9 != -1; n9--) {
                *p9++ = *q9++;
            }
        }
        return 6;
Ldef:
    puts(CD_str_unknown);
    printf(CD_str_pct, intr);
    return 0;
}
#endif