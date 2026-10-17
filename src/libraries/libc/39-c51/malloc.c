#include <malloc.h>
#include "library/psx_bios_tailjump.h"

void *malloc(u32 arg0) {
    PSX_BIOS_TAILJUMP(0xa0, 0x33);
}
