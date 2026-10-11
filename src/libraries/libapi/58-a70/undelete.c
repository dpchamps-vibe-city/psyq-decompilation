#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    long, undelete,
    (char *arg0),
    0xb0, 0x46
);
