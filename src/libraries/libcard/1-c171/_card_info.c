#include "library/psx_bios_tailjump.h"

long _card_info(long chan) {
    PSX_BIOS_TAILJUMP(0xa0, 0xab);
}
