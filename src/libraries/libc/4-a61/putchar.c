#include "library/psx_bios_tailjump.h"

void putchar(char arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0x3d);
}
