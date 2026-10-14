#include "library/psx_bios_tailjump.h"

long _card_wait(long drv) {
    PSX_BIOS_TAILJUMP(0xb0, 0x5d);
}
