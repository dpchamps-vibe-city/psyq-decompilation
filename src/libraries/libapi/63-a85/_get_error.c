#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    long, _get_error,
    (long arg0),
    0xb0, 0x55
);
