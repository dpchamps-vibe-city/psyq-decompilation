#include "library/psx_bios_tailjump.h"

long ioctl(long arg0, long arg1, long arg2) {
    PSX_BIOS_TAILJUMP(0xb0, 0x37);
}
