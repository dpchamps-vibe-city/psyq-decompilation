#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    char *, strstr,
    (const char *arg0, const char *arg1),
    0xa0, 0x24
);
