#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    int, strncmp,
    (const char *arg0, const char *arg1, int arg2),
    0xa0, 0x18
);
