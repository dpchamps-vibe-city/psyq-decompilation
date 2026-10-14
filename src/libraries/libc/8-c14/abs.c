#include "library/psx_bios_tailjump.h"

int abs(int arg0) {
    PSX_BIOS_TAILJUMP(0xa0, 0xe);
}
