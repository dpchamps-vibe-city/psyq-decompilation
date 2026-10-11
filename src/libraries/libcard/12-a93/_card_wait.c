#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    long, _card_wait,
    (long drv),
    0xb0, 0x5d
);
