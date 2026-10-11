#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    long, write,
    (long arg0, void *arg1, long arg2),
    0xb0, 0x35
);
