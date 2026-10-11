#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    void, ChangeClearPAD,
    (long arg0),
    0xb0, 0x5b
);
