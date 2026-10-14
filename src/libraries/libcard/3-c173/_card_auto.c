#include "library/psx_bios_tailjump.h"

long _card_auto(long val) {
    PSX_BIOS_TAILJUMP(0xa0, 0xad);
}
