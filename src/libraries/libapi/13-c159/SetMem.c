#include "library/psx_bios_tailjump.h"

void SetMem(long arg0) {
    PSX_BIOS_TAILJUMP(0xa0, 0x9f);
}
