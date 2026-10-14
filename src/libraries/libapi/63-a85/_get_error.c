#include "library/psx_bios_tailjump.h"

long _get_error(long arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0x55);
}
