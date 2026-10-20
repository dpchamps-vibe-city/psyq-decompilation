#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libpress.h>
#include <stdio.h>

s32 DMACallback();                     /* extern */

int DecDCTinCallback(void (*func)()) {
    return DMACallback(0, func);
}
