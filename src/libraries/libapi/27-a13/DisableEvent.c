#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    long, DisableEvent,
    (long arg0),
    0xb0, 0xd
);
