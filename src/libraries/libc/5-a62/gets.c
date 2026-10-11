#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    char *, gets,
    (char *arg0),
    0xb0, 0x3e
);
