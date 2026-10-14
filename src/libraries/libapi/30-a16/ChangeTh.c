#include "library/psx_bios_tailjump.h"

int ChangeTh(long arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0x10);
}
