#include "common.h"
#include <libsnd.h>
#include <libspu.h>

void SsUtReverbOff(void) {
    SpuSetReverb(0);
}
