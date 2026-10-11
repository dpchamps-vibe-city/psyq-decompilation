#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    long, _get_errno,
    (void),
    0xb0, 0x54
);
