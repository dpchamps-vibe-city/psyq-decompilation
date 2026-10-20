# libcd_20::CD_cw — human decision needed

- **Parked:** 2026-10-20T05:57:27.303Z
- **Reason:** escalation-exhausted
- **Escalation reached:** deepseek-v4-1-flash-1017
- **Source:** `src/libraries/libcd/20-bios_1/CD_cw.c` (image stub restored; library TU retained)
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
Oracle: libcd_20::CD_cw verdict MISMATCH — 1357/1376 words (98.62%).
Residual (steer by this, not the word count): control-flow 0, population 4, schedule 2, allocation 6.
The two programs do not contain the same instructions, so no allocation or scheduling reading applies yet — fix the semantics first.
Next block: 37 (0xE4C) — population 2, schedule 0, allocation 0. the instruction populations differ here; nothing below can be read until they agree
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.
```

## Preserved attempt

```c
#include "common.h"

extern int CD_debug;
extern char *CD_comstr[];
extern char *CD_intstr[];

extern s32 D_000019BC[2][64] __asm__("$LD_000019BC");
extern u8 CD_pos[];
extern u8 CD_mode;
extern u8 CD_com;

extern volatile u8 *D_00001B3C;
extern volatile u8 *D_00001B48;
extern volatile u8 *D_00001B4C;
extern volatile u8 D_00001B54[];
extern u8 B_00001B80[];
extern u8 B_00001B88[];
extern s32 B_00001B98 __asm__("$LB_00001B98");
extern s32 B_00001B9Crd __asm__("$LB_00001B98+4");
extern s32 B_00001B9Cwr __asm__("$LB_00001B9C");
extern char *B_00001BA0 __asm__("$LB_00001BA0");
extern void (*CD_cbready)(u8, u8 *);
extern void (*CD_cbsync)(u8, u8 *);

extern char RO_STR_0000174C[] __asm__("$LRO_STR_0000174C");
extern char RO_STR_0000175C[] __asm__("$LRO_STR_0000175C");
extern char RO_STR_000017E8[] __asm__("$LRO_STR_000017E8");
extern char RO_STR_000017F0[] __asm__("$LRO_STR_000017F0");
extern char RO_STR_00001800[] __asm__("$LRO_STR_00001800");

extern s32 CD_sync(s32, u8 *);
extern void CD_flush(void);
extern int CheckCallback(void);
extern int VSync(int);
extern int printf(const char *, ...);
extern int puts(const char *);

int CD_cw(u8 com, u8 *param, u8 *result, int mode) {
    u8 *p;
    u8 *q;
    s32 i;
    s32 n;
    s32 cb;
    s32 ret;
    s32 cnt;
    s32 old;
    s32 r;
    u8 intr;
    char **comstr;
    char **intstr;

    if (CD_debug >= 2) {
        printf(RO_STR_000017E8, CD_comstr[com]);
    }
    if (D_000019BC[1][com] != 0 && param == 0) {
        if (CD_debug > 0) {
            printf(RO_STR_000017F0, CD_comstr[com]);
        }
        return -2;
    }
    CD_sync(0, 0);
    if (com == 2) {
        for (i = 0; i < 4; i++) {
            CD_pos[i] = param[i];
        }
    }
    if (com == 0xE) {
        CD_mode = *param;
    }
    D_00001B54[0] = 0;
    if (D_000019BC[0][com] != 0) {
        D_00001B54[1] = 0;
    }
    *D_00001B3C = 0;
    for (i = 0; i < D_000019BC[1][com]; i++) {
        *D_00001B4C = param[i];
    }
    CD_com = com;
    *D_00001B48 = com;
    if (mode != 0) {
        return 0;
    }
    B_00001B98 = VSync(-1) + 0x3C0;
    B_00001B9Cwr = 0;
    B_00001BA0 = RO_STR_00001800;
    while (D_00001B54[0] == 0) {
        comstr = CD_comstr;
        intstr = CD_intstr;
        if (B_00001B98 < VSync(-1) || (cnt = B_00001B9Crd, old = cnt, B_00001B9Cwr = ++cnt, old > 0x3C0000)) {
            puts(RO_STR_0000174C);
            printf(RO_STR_0000175C, B_00001BA0, comstr[CD_com],
                   intstr[D_00001B54[0]], intstr[D_00001B54[1]]);
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
    }
    q = result;
    if (q != 0) {
        p = B_00001B80;
        for (n = 7; n != -1; n--) {
            *q++ = *p++;
        }
    }
    r = 0;
    if (D_00001B54[0] == 5) {
        r = -1;
    }
    return r;
}
```
