#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    long, _card_info,
    (long chan),
    0xa0, 0xab
);
