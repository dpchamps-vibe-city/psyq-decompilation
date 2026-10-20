#include "common.h"
#include <libspu.h>

u32 _spu_FgetRXXa();                            /* extern */

unsigned long SpuGetIRQAddr(void) {
    return _spu_FgetRXXa(0xD2, -2);
}
