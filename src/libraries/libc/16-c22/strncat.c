#include "library/psx_bios_tailjump.h"

char *strncat(char *arg0, const char *arg1, int arg2) {
    PSX_BIOS_TAILJUMP(0xa0, 0x16);
}
