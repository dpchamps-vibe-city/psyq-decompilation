#include "library/psx_bios_tailjump.h"

char *gets(char *arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0x3e);
}
