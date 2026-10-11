#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    void, putchar,
    (char arg0),
    0xb0, 0x3d
);
