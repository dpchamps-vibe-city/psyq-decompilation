#include "library/psx_bios_tailjump.h"

long erase(char *arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0x45);
}
