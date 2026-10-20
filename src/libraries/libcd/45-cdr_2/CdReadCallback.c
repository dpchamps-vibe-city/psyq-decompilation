#include "common.h"
#include <sys/types.h>
#include <libcd.h>

extern void (*CD_cbread)(u8, u8 *);

void (*CdReadCallback(void (*func)(u8, u8 *)))(u8, u8 *) {
    void (*temp_v0)(u8, u8 *);

    temp_v0 = CD_cbread;
    CD_cbread = func;
    return temp_v0;
}
