#include "common.h"
#include <sys/types.h>
#include <libetc.h>

extern void (*CD_cbready)(u8, u8 *);
extern void (*CD_cbsync)(u8, u8 *);
extern s32 CD_status;
extern s32 CD_status1;

s32 InterruptCallback(s32, void (*)(void));
static void func_00001534(void) __asm__("$Lfunc_00001534");

void CD_initintr(void) {
    CD_cbready = 0;
    CD_cbsync = 0;
    CD_status1 = 0;
    CD_status = 0;
    ResetCallback();
    InterruptCallback(2, func_00001534);
}
