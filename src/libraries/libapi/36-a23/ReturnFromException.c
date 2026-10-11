#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    void, ReturnFromException,
    (void),
    0xb0, 0x17
);
