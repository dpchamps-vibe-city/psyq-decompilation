INCLUDE_ASM("build/libraries/nonmatchings/libc2_12", putchar);

/* PSX parked attempt: preserved reconstruction from before the provenance switch. */
#if 0
#include "common.h"
#include <ctype.h>

extern s32 D_000002D0;
extern s32 D_000002D4;
extern s8 B_000002E0[];

void putchar(s8 c) {
    switch (c) {
    case '\n':
        _putchar('\r');
        D_000002D0 = 0;
        break;
    case '\t':
        do {
            _putchar(' ');
        } while (D_000002D0 & 7);
        goto flush;
    default:
        if ((((signed char *)(_ctype_ + 1))[(unsigned char)(c)] & 0x97)) {
            D_000002D0++;
        }
        break;
    }
    if (D_000002D4 >= 0x20) {
        write(1, B_000002E0, D_000002D4);
        D_000002D4 = 0;
    }
    {
        s32 n = D_000002D4;
        B_000002E0[n] = c;
        D_000002D4 = n + 1;
    }
flush:
    if (D_000002D4 > 0) {
        write(1, B_000002E0, D_000002D4);
        D_000002D4 = 0;
    }
}
#endif
