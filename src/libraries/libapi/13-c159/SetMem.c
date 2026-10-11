#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    void, SetMem,
    (long arg0),
    0xa0, 0x9f
);
