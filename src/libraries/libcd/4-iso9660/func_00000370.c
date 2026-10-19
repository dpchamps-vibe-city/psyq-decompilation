INCLUDE_ASM("build/libraries/nonmatchings/libcd_4", func_00000370);


/* PARKED by /auto_decompilation_loop on 2026-10-19T22:22:17.308Z.
 * Reason: escalation-exhausted.
 * Escalation reached: deepseek-v4-1-flash-1017.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libcd_4::func_00000370.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <stdio.h>

extern u8 $LB_000027E8[];
extern u32 $LD_00000BD8;

typedef struct {
    u32 number;
    u32 parent;
    u32 lba;
    char name[32];
} DirEntry;

typedef struct {
    u8 b[4];
} Word4;

extern DirEntry $LB_000011E8[];

extern void *memcpy(void *, void *, u32);
extern s32 strncmp(s8 *, s8 *, s32);
extern s32 func_00000974(s32, s32, u8 *) __asm__("$Lfunc_00000974");

extern char str_pvd_err[] __asm__("$LRO_STR_00000A74");
extern char str_cd001[] __asm__("$LRO_STR_00000AA0");
extern char str_fmt_err[] __asm__("$LRO_STR_00000AA8");
extern char str_pt_err[] __asm__("$LRO_STR_00000AD8");
extern char str_search[] __asm__("$LRO_STR_00000AFC");
extern char str_entry[] __asm__("$LRO_STR_00000B1C");
extern char str_count[] __asm__("$LRO_STR_00000B30");

static s32 func_00000370(void) {
    u8 *p;
    u8 *pvd;
    u8 *end;
    u32 pt;
    u32 n;
    u32 m;
    s32 stat;
    s32 i;

    pvd = $LB_000027E8;
    stat = func_00000974(1, 0x10, pvd);
    if (stat != 1) {
        if (CD_debug > 0) {
            printf(str_pvd_err);
        }
        return 0;
    }
    if (strncmp((s8 *)&pvd[1], (s8 *)str_cd001, 5) != 0) {
        if (CD_debug > 0) {
            printf(str_fmt_err);
        }
        return 0;
    }
    *(Word4 *)&pt = *(Word4 *)(pvd + 0x8C);
    if (func_00000974(1, pt, pvd) != stat) {
        if (CD_debug > 0) {
            printf(str_pt_err, pt);
        }
        return 0;
    }
    if (CD_debug >= 2) {
        printf(str_search);
    }
    p = pvd;
    i = 0;
    if (p < pvd + 0x800) {
        end = pvd + 0x800;
        do {
            if (p[0] != 0) {
                *(Word4 *)&$LB_000011E8[i].lba = *(Word4 *)(p + 2);
                $LB_000011E8[i].parent = p[6];
                $LB_000011E8[i].number = i + 1;
                memcpy($LB_000011E8[i].name, p + 8, p[0]);
                $LB_000011E8[i].name[p[0]] = 0;
                n = p[0];
                m = n & 1;
                m += 8;
                p += n + m;
                if (CD_debug >= 2) {
                    printf(str_entry, $LB_000011E8[i].lba, $LB_000011E8[i].number,
                           $LB_000011E8[i].parent, $LB_000011E8[i].name);
                }
                i++;
            } else {
                break;
            }
        } while (i < 128 && p < end);
    }
    if (i < 128) {
        $LB_000011E8[i].parent = 0;
    }
    $LD_00000BD8 = 0;
    if (CD_debug >= 2) {
        printf(str_count, i);
    }
    return 1;
}
#endif
