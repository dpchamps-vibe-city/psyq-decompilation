#include <malloc.h>
#include "library/psx_bios_tailjump.h"

void *realloc(void *arg0, u32 arg1) {
    PSX_BIOS_TAILJUMP(0xa0, 0x38);
}
