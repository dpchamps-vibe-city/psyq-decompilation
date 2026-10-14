#include "library/psx_bios_tailjump.h"

void putc(char arg0, int arg1) {
    PSX_BIOS_TAILJUMP(0xb0, 0x3b);
}
