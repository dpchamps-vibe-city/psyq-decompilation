#include "library/psx_bios_tailjump.h"

void SystemError(char arg0, long arg1) {
    PSX_BIOS_TAILJUMP(0xa0, 0xa1);
}
