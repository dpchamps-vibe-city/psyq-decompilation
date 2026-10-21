#include "common.h"

extern void CD_flush(void);
extern void (*CD_cbsync)(u8, u8 *);
extern void (*CD_cbready)(u8, u8 *);
extern void VSyncCallbacks(s32, void (*)(u8, u8 *, s32 *, s32 *));

void DS_close(void) {
    D_00001240.active = 0;
    CD_flush();
    CD_cbsync = 0;
    CD_cbready = 0;
    VSyncCallbacks(0, 0);
}
