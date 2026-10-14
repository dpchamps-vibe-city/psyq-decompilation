#include "library/psx_bios_tailjump.h"

char *strncpy(char *arg0, const char *arg1, int arg2) {
    PSX_BIOS_TAILJUMP(0xa0, 0x1a);
}
