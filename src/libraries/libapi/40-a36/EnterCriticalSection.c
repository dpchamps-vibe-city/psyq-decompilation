#include "library/psx_bios.h"

int EnterCriticalSection(void) {
    return PSX_BIOS_SYSCALL(1);
}
