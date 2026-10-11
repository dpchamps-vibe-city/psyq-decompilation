#include "library/psx_bios.h"

void Exception(void) {
    (void)PSX_BIOS_SYSCALL(0);
}
