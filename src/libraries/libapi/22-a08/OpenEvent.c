#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    long, OpenEvent,
    (unsigned long arg0, long arg1, long arg2, long (*func)()),
    0xb0, 0x8
);
