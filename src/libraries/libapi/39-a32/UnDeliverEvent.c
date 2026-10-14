#include "library/psx_bios_tailjump.h"

void UnDeliverEvent(unsigned long arg0, unsigned long arg1) {
    PSX_BIOS_TAILJUMP(0xb0, 0x20);
}
