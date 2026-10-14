#include "library/psx_bios_tailjump.h"

long _card_load(long chan) {
    PSX_BIOS_TAILJUMP(0xa0, 0xac);
}
