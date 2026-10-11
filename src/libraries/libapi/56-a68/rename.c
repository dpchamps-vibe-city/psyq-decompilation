#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    long, rename,
    (char *arg0, char *arg1),
    0xb0, 0x44
);
