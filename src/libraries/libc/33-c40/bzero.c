#include "library/psx_bios_tailjump.h"

void *bzero(unsigned char *arg0, int arg1) {
    PSX_BIOS_TAILJUMP(0xa0, 0x28);
}
