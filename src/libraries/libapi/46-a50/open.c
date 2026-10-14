#include "library/psx_bios_tailjump.h"

long open(char *arg0, unsigned long arg1) {
    PSX_BIOS_TAILJUMP(0xb0, 0x32);
}
