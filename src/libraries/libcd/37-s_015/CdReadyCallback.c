#include "common.h"
#include <sys/types.h>
#include <libcd.h>

extern void (*CD_cbready)(u8, u8 *);

void (*CdReadyCallback(void (*func)(u8, u8 *)))(u8, u8 *) {
    void (*temp_v0)(u8, u8 *);

    temp_v0 = CD_cbready;
    CD_cbready = func;
    return temp_v0;
}
