#include "library/psx_bios_tailjump.h"

void ReturnFromException(void) {
    PSX_BIOS_TAILJUMP(0xb0, 0x17);
}
