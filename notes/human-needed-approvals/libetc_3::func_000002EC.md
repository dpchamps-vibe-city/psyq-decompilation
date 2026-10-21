# libetc_3::func_000002EC — human decision needed

- **Parked:** 2026-10-21T09:35:54.283Z
- **Reason:** escalation-exhausted
- **Escalation reached:** deepseek-v4-1-flash-1017
- **Source:** `src/libraries/libetc/3-intr/func_000002EC.c` (image stub restored; library TU retained)
- **Preserved attempt:** library measurements have no staged ranking; kept the current complete TU, including neighboring functions/data
- **Parking notes:** attempt is itself an INCLUDE_ASM stub; nothing to preserve; src/libraries/libetc/3-intr/GetIntrMask.c: pre-attempt source restored; attempt archived at /home/dave/Documents/code/psyq-decomp/run_output/autoloop/attempts/libetc_3::func_000002EC.GetIntrMask.c.2026-10-21T09-35-54-283Z.parked.c

## What the loop needs

Every tier on the escalation ladder returned without a byte-exact match. The function
needs either a new structural hypothesis or a policy decision that the ladder cannot
make on its own. The preserved attempt and the oracle report below are the starting
point.

## Policy findings

- none recorded

## Oracle report for the preserved attempt

```
Oracle: libetc_3::func_000002EC verdict STUB — the source still hands the function to the assembler.
No C has been written for it yet, so there is no candidate program, no word count and no residual.
Write the function body. Every number below the verdict starts existing once you do.
```

## Preserved attempt

```c
INCLUDE_ASM("build/libraries/nonmatchings/libetc_3", func_000002EC);

/* PARKED build-only attempt: the named entry's clean C.
 *
 * The target's inferred extent (.text 0x26C-0x69C) also contains three
 * independent private entries (T_000004BC, T_00000604, T_000006A4) published
 * only by .data R_MIPS32 words.  The single-function TU part gate refuses a
 * second definition in this file, and the installed private-entry discovery
 * does not split non-code R_MIPS32 published code addresses.  Re-enable only
 * after that partition is corrected; the active INCLUDE_ASM stub above keeps
 * the whole member byte-exact meanwhile.
 *
 * Measured build-only with the original trailing helper assembly appended:
 * 89/116 target words of the named entry; whole compound 167/432.
 * Best candidate: build/candidates/func_000002EC/v35.c
 * Runner: build/exp/ec/measure.mjs
 */
#if 0
#include "common.h"
#include <libapi.h>
#include <sys/types.h>
#include <libetc.h>
#include <setjmp.h>
#include <stdio.h>

typedef struct {
    u16 intr;
    u16 active;
    void (*handler[11])(void);
    u16 mask;
    u16 saved_mask;
    u32 entry;
} Intr;

extern Intr D_00000808;
extern u16 D_0000080A;
extern u16 D_00000838;
extern volatile u16 *D_00001894;
extern volatile u16 *D_00001898;
extern s32 D_000018A0;
extern char RO_STR_00000774[];
extern char RO_STR_00000790[];

void func_000002EC(void) {
    Intr *p;
    s32 i;
    u16 pending;
    u16 check;
    u16 mask;
    void (**handler)(void);
    void (**base)(void);

    p = &D_00000808;
    if (p->intr == 0) {
        printf(RO_STR_00000774, *D_00001894);
        ReturnFromException();
    }
    p->active = 1;
    mask = p->mask & *D_00001894;
    check = *D_00001898 & mask;
    if (check != 0) {
        pending = check;
        base = p->handler;
        do {
            i = 0;
            handler = base;
            for (; pending != 0 && i < 0xB; i++) {
                if (pending & 1) {
                    *D_00001894 = ~(1 << i);
                    if (*handler != 0)
                        (*handler)();
                }
                handler++;
                pending >>= 1;
            }
            mask = D_00000838 & *D_00001894;
            check = *D_00001898 & mask;
            pending = check;
        } while (check != 0);
    }
    if (*D_00001894 & *D_00001898) {
        if (D_000018A0++ >= 0x801) {
            printf(RO_STR_00000790, *D_00001894, *D_00001898);
            D_000018A0 = 0;
            *D_00001894 = 0;
        }
    } else {
        D_000018A0 = 0;
    }
    D_0000080A = 0;
    ReturnFromException();
}
#endif
```
