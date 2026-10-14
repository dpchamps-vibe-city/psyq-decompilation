#include "library/psx_bios_tailjump.h"

long OpenTh(long (*func)(), unsigned long arg1, unsigned long arg2) {
    PSX_BIOS_TAILJUMP(0xb0, 0xe);
}
