#include "library/psx_bios.h"

void ExitCriticalSection(void) {
    (void)PSX_BIOS_SYSCALL(2);
}
