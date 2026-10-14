#include "library/psx_bios_tailjump.h"

long format(char *arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0x41);
}
