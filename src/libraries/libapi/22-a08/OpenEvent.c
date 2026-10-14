#include "library/psx_bios_tailjump.h"

long OpenEvent(unsigned long arg0, long arg1, long arg2, long (*func)()) {
    PSX_BIOS_TAILJUMP(0xb0, 0x8);
}
