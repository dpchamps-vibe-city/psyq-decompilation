#include "common.h"
#include <libspu.h>

u32 _SpuGetAnyVoice();                          /* extern */

unsigned long SpuGetNoiseVoice(void) {
    return _SpuGetAnyVoice(0xCA, 0xCB);
}
