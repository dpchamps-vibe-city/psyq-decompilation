#include "common.h"
#include <libsnd.h>
#include <libspu.h>

void SsSetNck(short arg0) {
    SpuSetNoiseClock((s32) arg0);
}
