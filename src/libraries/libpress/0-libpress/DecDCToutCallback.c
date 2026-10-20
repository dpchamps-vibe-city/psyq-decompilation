#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libpress.h>
#include <stdio.h>

s32 DMACallback();                     /* extern */

int DecDCToutCallback(void (*func)()) {
    return DMACallback(1, func);
}
