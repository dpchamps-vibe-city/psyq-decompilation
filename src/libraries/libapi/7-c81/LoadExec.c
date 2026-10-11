#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    long, LoadExec,
    (char *arg0, unsigned long arg1, unsigned long arg2),
    0xa0, 0x51
);
