#include "library/psx_bios_tailjump.h"

char *strcpy() {
    PSX_BIOS_TAILJUMP(0xa0, 0x19);
}
