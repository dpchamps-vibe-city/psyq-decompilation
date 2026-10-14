#include "library/psx_bios_tailjump.h"

long _get_errno(void) {
    PSX_BIOS_TAILJUMP(0xb0, 0x54);
}
