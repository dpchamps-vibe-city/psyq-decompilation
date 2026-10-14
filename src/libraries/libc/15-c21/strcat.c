#include "library/psx_bios_tailjump.h"

char *strcat(char *arg0, const char *arg1) {
    PSX_BIOS_TAILJUMP(0xa0, 0x15);
}
