#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    long, ioctl,
    (long arg0, long arg1, long arg2),
    0xb0, 0x37
);
