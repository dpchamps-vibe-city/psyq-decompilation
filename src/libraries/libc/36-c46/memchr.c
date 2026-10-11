#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    void *, memchr,
    (const unsigned char *arg0, unsigned char arg1, int arg2),
    0xa0, 0x2e
);
