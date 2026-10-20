#include "common.h"
#include <libspu.h>

u32 _SpuGetAnyVoice();                          /* extern */

unsigned long SpuGetReverbVoice(void) {
    return _SpuGetAnyVoice(0xCC, 0xCD);
}
