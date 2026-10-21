#include "common.h"
#include <sys/types.h>
#include <libds.h>

extern void (*GlobalCallback)(u8, u8 *);

void (*DsSyncCallback(void (*func)(u8, u8 *)))(u8, u8 *) {
    void (*temp_v0)(u8, u8 *);
    u8 *gp;

    gp = (u8 *)&GlobalCallback;
    temp_v0 = *(void (**)(u8, u8 *))(gp + 0);
    *(void (**)(u8, u8 *))(gp + 0) = func;
    return temp_v0;
}
