#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    long, _card_write,
    (long chan, long block, unsigned char *buf),
    0xb0, 0x4e
);
