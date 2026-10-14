#include "library/psx_bios_tailjump.h"

char *strchr(const char *arg0, char arg1) {
    PSX_BIOS_TAILJUMP(0xa0, 0x1e);
}
