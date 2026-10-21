#include "common.h"
#include <sys/types.h>
#include <libds.h>

extern void (*GlobalCallback)(u8, u8 *);

void (*DsReadyCallback(void (*func)(u8, u8 *)))(u8, u8 *) {
    void (*temp_v0)(u8, u8 *);

    temp_v0 = ((void (**)(u8, u8 *))&GlobalCallback)[1];
    ((void (**)(u8, u8 *))&GlobalCallback)[1] = func;
    return temp_v0;
}
