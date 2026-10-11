#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    char *, index,
    (const char *arg0, char arg1),
    0xa0, 0x1c
);
