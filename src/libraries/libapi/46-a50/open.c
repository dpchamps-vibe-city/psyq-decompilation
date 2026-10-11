#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    long, open,
    (char *arg0, unsigned long arg1),
    0xb0, 0x32
);
