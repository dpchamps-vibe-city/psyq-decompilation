#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    long, _card_auto,
    (long val),
    0xa0, 0xad
);
