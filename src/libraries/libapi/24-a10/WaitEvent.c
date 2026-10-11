#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    long, WaitEvent,
    (long arg0),
    0xb0, 0xa
);
