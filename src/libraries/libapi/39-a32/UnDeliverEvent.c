#include "library/psx_bios_tailjump.h"

PSX_BIOS_FUNCTION(
    void, UnDeliverEvent,
    (unsigned long arg0, unsigned long arg1),
    0xb0, 0x20
);
