#include "library/psx_bios_tailjump.h"

long WaitEvent(long arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0xa);
}
