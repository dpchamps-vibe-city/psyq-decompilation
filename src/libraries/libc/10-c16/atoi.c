#include "library/psx_bios_tailjump.h"

int atoi(const char *arg0) {
    PSX_BIOS_TAILJUMP(0xa0, 0x10);
}
