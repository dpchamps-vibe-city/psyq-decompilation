#include "library/psx_bios_tailjump.h"

long TestEvent(long arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0xb);
}
