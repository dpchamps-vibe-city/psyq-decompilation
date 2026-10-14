#include "library/psx_bios_tailjump.h"

extern void *B_00000118;

void EnablePAD(void) {
    PSX_BIOS_TAILJUMP_LOAD(B_00000118);
}
