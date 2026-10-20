# libcd_20::CD_datasync — human decision needed

- **Parked:** 2026-10-20T06:42:40.128Z
- **Reason:** escalation-exhausted
- **Escalation reached:** deepseek-v4-1-flash-1017
- **Source:** `src/libraries/libcd/20-bios_1/CD_datasync.c` (image stub restored; library TU retained)
- **Preserved attempt:** library measurements have no staged ranking; kept the current complete TU, including neighboring functions/data
- **Parking notes:** attempt is itself an INCLUDE_ASM stub; nothing to preserve

## What the loop needs

Every tier on the escalation ladder returned without a byte-exact match. The function
needs either a new structural hypothesis or a policy decision that the ladder cannot
make on its own. The preserved attempt and the oracle report below are the starting
point.

## Policy findings

- none recorded

## Oracle report for the preserved attempt

```
Oracle: libcd_20::CD_datasync verdict STUB — the source still hands the function to the assembler.
No C has been written for it yet, so there is no candidate program, no word count and no residual.
Write the function body. Every number below the verdict starts existing once you do.
```

## Preserved attempt

```c
INCLUDE_ASM("build/libraries/nonmatchings/libcd_20", CD_datasync);


/* PARKED by /auto_decompilation_loop on 2026-10-20T23:59:00.000Z.
 * Reason: escalation-exhausted (single-tier ladder) with a witnessed capability
 * blocker: the scheduler/local-alloc observability tools refuse relocatable
 * library members, and the residual is one pre-local-alloc block order plus one
 * quantity split in block 3 (cfg 0, population 0, schedule 2, allocation 6).
 * Escalation reached: deepseek-v4-1-flash-1017.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libcd_20::CD_datasync.md
 */

#if 0
/* Best non-matching attempt (v5), preserved for the next session. */
#include "common.h"

extern s32 B_00001B98 __asm__("$LB_00001B98");
extern s32 B_00001B9C __asm__("$LB_00001B9C");
extern char *B_00001BA0 __asm__("$LB_00001BA0");
extern s32 *D_00001B70 __asm__("$LD_00001B70");
extern volatile u8 D_00001B54[];
extern u8 CD_com;
extern char *CD_comstr[];
extern char *CD_intstr[];
extern char RO_STR_0000174C[] __asm__("$LRO_STR_0000174C");
extern char RO_STR_0000175C[] __asm__("$LRO_STR_0000175C");
extern char RO_STR_00001858[] __asm__("$LRO_STR_00001858");

extern s32 VSync(s32);
extern void CD_flush(void);
extern int printf(const char *, ...);
extern int puts(const char *);

s32 CD_datasync(s32 mode) {
    s32 ret;
    s32 cnt;
    s32 old;
    s32 limit;

    B_00001B98 = VSync(-1) + 0x3C0;
    B_00001B9C = 0;
    B_00001BA0 = RO_STR_00001858;
    limit = 0x3C0000;
    while (1) {
        if (B_00001B98 < VSync(-1) || (cnt = B_00001B9C, old = cnt, B_00001B9C = ++cnt, old > limit)) {
            puts(RO_STR_0000174C);
            printf(RO_STR_0000175C, B_00001BA0, CD_comstr[CD_com],
                   CD_intstr[D_00001B54[0]], CD_intstr[D_00001B54[1]]);
            CD_flush();
            ret = -1;
        } else {
            ret = 0;
        }
        if (ret != 0) {
            return -1;
        }
        if (*D_00001B70 & 0x01000000) {
            if (mode == 0) {
                continue;
            }
            return 1;
        }
        return 0;
    }
}
#endif
```
