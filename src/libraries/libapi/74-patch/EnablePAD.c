#include "common.h"

extern void *B_00000118;

#define PSX_BIOS_TAILJUMP_LOAD(destination) \
    do { \
        register void *__psx_bios_entry __asm__("$9") = (destination); \
        goto *__psx_bios_entry; \
    } while (0)

void EnablePAD(void) {
    PSX_BIOS_TAILJUMP_LOAD(B_00000118);
}
