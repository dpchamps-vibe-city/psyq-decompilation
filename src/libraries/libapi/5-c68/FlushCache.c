#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    void, FlushCache,
    (void),
    0xa0, 0x44
);
