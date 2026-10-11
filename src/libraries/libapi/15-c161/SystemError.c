#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    void, SystemError,
    (char arg0, long arg1),
    0xa0, 0xa1
);
