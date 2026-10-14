#include "library/psx_bios_tailjump.h"

void free(void *arg0) {
    PSX_BIOS_TAILJUMP(0xa0, 0x34);
}
