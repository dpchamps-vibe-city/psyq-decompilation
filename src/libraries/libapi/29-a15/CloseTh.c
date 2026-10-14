#include "library/psx_bios_tailjump.h"

int CloseTh(long arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0xf);
}
