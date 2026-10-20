#include "common.h"
#include <libsio.h>

s32 InterruptCallback();               /* extern */

int Sio1Callback(void (*func)()) {
    return InterruptCallback(8, func);
}
