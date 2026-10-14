#include "library/psx_bios_tailjump.h"

char getchar(void) {
    PSX_BIOS_TAILJUMP(0xb0, 0x3c);
}
