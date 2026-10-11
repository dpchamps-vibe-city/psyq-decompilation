#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    char *, strncat,
    (char *arg0, const char *arg1, int arg2),
    0xa0, 0x16
);
