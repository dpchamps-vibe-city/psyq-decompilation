#include "library/psx_bios_tailjump.h"

void *bcopy(const unsigned char *arg0, unsigned char *arg1, int arg2) {
    PSX_BIOS_TAILJUMP(0xa0, 0x27);
}
