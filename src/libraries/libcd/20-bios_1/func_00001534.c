#include "common.h"

extern volatile u8 *D_00001B3C;
extern volatile u8 D_00001B54[];
extern u8 B_00001B80[];
extern u8 B_00001B88[];
extern void (*CD_cbready)(u8, u8 *);
extern void (*CD_cbsync)(u8, u8 *);
extern s32 func_00000090(void);

static void func_00001534(void) __asm__("$Lfunc_00001534");

static void func_00001534(void) {
    u8 intr;
    s32 cb;

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
