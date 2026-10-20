# libcd_20::CD_sync — human decision needed

- **Parked:** 2026-10-20T02:43:03.082Z
- **Reason:** escalation-exhausted
- **Escalation reached:** deepseek-v4-1-flash-1017
- **Source:** `src/libraries/libcd/20-bios_1/CD_sync.c` (image stub restored; library TU retained)
- **Preserved attempt:** library measurements have no staged ranking; kept the current complete TU, including neighboring functions/data

## What the loop needs

Every tier on the escalation ladder returned without a byte-exact match. The function
needs either a new structural hypothesis or a policy decision that the ladder cannot
make on its own. The preserved attempt and the oracle report below are the starting
point.

## Policy findings

- none recorded

## Oracle report for the preserved attempt

```
Oracle: libcd_20::CD_sync verdict MISMATCH — 1350/1376 words (98.11%).
Residual (steer by this, not the word count): control-flow 0, population 3, schedule 4, allocation 5.
The two programs do not contain the same instructions, so no allocation or scheduling reading applies yet — fix the semantics first.
Next block: 6 (0x6A4) — population 1, schedule 0, allocation 0. the instruction populations differ here; nothing below can be read until they agree
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.
```

## Preserved attempt

```c
#include "common.h"

extern volatile u8 *D_00001B3C;
extern volatile u8 D_00001B54[];
extern u8 B_00001B80[];
extern u8 B_00001B88[];
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
extern char RO_STR_000017D4[] __asm__("$LRO_STR_000017D4");

extern s32 VSync(s32);
extern s32 CheckCallback(void);
extern s32 func_00000090(void);
extern void CD_flush(void);
extern int printf(const char *, ...);
extern int puts(const char *);

s32 CD_sync(s32 mode, u8 *result) {
    s32 i;
    s32 cb;
    s32 n;
    s32 ret;
    s32 cnt;
    s32 old;
    u8 intr;
    u8 *p;
    u8 *q;
    u8 *intr_state;
    u8 *intr1_state;
    char **comstr;
    char **intstr;

    B_00001B98 = VSync(-1) + 0x3C0;
    B_00001B9Cwr = 0;
    B_00001BA0 = RO_STR_000017D4;
    comstr = CD_comstr;
    intstr = CD_intstr;
    intr_state = D_00001B54;
    intr1_state = D_00001B54 + 1;
    while (1) {
        if (B_00001B98 < VSync(-1) || (cnt = B_00001B9Crd, old = cnt, B_00001B9Cwr = ++cnt, old > 0x3C0000)) {
            puts(RO_STR_0000174C);
            i = intr_state[0];
            printf(RO_STR_0000175C, B_00001BA0, comstr[CD_com],
                   intstr[i], intstr[intr_state[1]]);
            CD_flush();
            ret = -1;
        } else {
            ret = 0;
        }
        if (ret != 0) {
            return ret;
        }
        if (CheckCallback()) {
            intr = *D_00001B3C & 3;
            while ((cb = func_00000090()) != 0) {
                if (cb & 4) {
                    if (CD_cbready != 0) {
                        CD_cbready(intr1_state[0], B_00001B88);
                    }
                }
                if ((cb & 2) && CD_cbsync != 0) {
                    CD_cbsync(intr_state[0], B_00001B80);
                }
            }
            *D_00001B3C = intr;
        }
        i = intr_state[0];
        if ((i & 0xFF) == 2 || (i & 0xFF) == 5) {
            intr_state[0] = 2;
            q = result;
            p = B_00001B80;
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
```
