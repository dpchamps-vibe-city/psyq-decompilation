#include "library/psx_bios_tailjump.h"

long LoadExec(char *arg0, unsigned long arg1, unsigned long arg2) {
    PSX_BIOS_TAILJUMP(0xa0, 0x51);
}
