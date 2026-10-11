#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    long, _card_read,
    (long chan, long block, unsigned char *buf),
    0xb0, 0x4f
);
