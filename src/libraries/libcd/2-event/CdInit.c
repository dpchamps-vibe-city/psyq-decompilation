#include "common.h"
#include <stdio.h>

static s32 func_00000108(void) __asm__("$Lfunc_00000108");
extern void func_00000144(void) __asm__("$Lfunc_00000144");
extern void func_0000016C(void) __asm__("$Lfunc_0000016C");
extern void func_00000194(void) __asm__("$Lfunc_00000194");

extern void (*CD_cbsync)(void);
extern char CdInit_failed[] __asm__("$LRO_STR_000001C8");
extern void (*CD_cbready)(void);
extern void (*CD_cbread)(void);
extern s32 CD_read_dma_mode;

s32 CdInit(void) {
    s32 i;

    i = 4;
    while (func_00000108() != 1) {
        i -= 1;
        if (i == -1) {
            printf(CdInit_failed);
            return 0;
        }
    }
    CD_cbsync = func_00000144;
    CD_cbready = func_0000016C;
    CD_cbread = func_00000194;
    CD_read_dma_mode = 0;
    return 1;
}
