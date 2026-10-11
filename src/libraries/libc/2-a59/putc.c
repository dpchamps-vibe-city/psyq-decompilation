#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    void, putc,
    (char arg0, int arg1),
    0xb0, 0x3b
);
