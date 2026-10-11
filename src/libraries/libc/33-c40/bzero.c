#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    void *, bzero,
    (unsigned char *arg0, int arg1),
    0xa0, 0x28
);
