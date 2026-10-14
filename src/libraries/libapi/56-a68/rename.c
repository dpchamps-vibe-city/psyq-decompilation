#include "library/psx_bios_tailjump.h"

long rename(char *arg0, char *arg1) {
    PSX_BIOS_TAILJUMP(0xb0, 0x44);
}
