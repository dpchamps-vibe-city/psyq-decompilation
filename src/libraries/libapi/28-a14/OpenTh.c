#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    long, OpenTh,
    (long (*func)(), unsigned long arg1, unsigned long arg2),
    0xb0, 0xe
);
