#include "library/psx_bios_tailjump.h"

long read(long arg0, void *arg1, long arg2) {
    PSX_BIOS_TAILJUMP(0xb0, 0x34);
}
