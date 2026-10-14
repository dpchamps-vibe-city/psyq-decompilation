#include "library/psx_bios_tailjump.h"

void ChangeClearPAD(long arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0x5b);
}
