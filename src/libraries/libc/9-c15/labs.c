#include "library/psx_bios_tailjump.h"

long labs(long arg0) {
    PSX_BIOS_TAILJUMP(0xa0, 0xf);
}
