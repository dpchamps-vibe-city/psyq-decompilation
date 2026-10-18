INCLUDE_ASM("build/libraries/nonmatchings/libc2_12", _putchar_flash);

/* PSX parked attempt: preserved reconstruction from before the provenance switch. */
#if 0
#include "common.h"

void _putchar_flash(void) {
    if (D_000002D4 > 0) {
        write(1, B_000002E0, D_000002D4);
        D_000002D4 = 0;
    }
}
#endif
