#include "common.h"
#include <sys/types.h>
#include <libcd.h>

extern void (*CD_cbsync)(u8, u8 *);

void (*CdSyncCallback(void (*func)(u8, u8 *)))(u8, u8 *) {
    void (*temp_v0)(u8, u8 *);

    temp_v0 = CD_cbsync;
    CD_cbsync = func;
    return temp_v0;
}
