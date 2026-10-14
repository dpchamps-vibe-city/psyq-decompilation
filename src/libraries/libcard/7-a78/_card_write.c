#include "library/psx_bios_tailjump.h"

long _card_write(long chan, long block, unsigned char *buf) {
    PSX_BIOS_TAILJUMP(0xb0, 0x4e);
}
