#include "common.h"

s16 SpuGetNoiseClock();                             /* extern */

s16 SsGetNck(void) {
    return SpuGetNoiseClock();
}
