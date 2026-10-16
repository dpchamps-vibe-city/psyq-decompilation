#include "library/psx_bios_tailjump.h"

unsigned long GetSysSp(void) {
    PSX_BIOS_TAILJUMP(0xa0, 0x52);
}
