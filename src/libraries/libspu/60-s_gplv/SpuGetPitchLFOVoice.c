#include "common.h"
#include <libspu.h>

u32 _SpuGetAnyVoice();                          /* extern */

unsigned long SpuGetPitchLFOVoice(void) {
    return _SpuGetAnyVoice(0xC8, 0xC9);
}
