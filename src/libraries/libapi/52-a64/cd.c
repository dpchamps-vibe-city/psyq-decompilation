#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    long, cd,
    (char *arg0),
    0xb0, 0x40
);
