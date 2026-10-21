#include "common.h"
#include "library/11-putc.h"
#include <ctype.h>

extern s32 D_000002D0;
extern s32 D_000002D4;
extern s8 B_000002E0[];

void _putchar(s8 c) {
    switch (c) {
    case '\n':
        _putchar('\r');
        D_000002D0 = 0;
        break;
    case '\t':
        do {
            _putchar(' ');
        } while (D_000002D0 & 7);
        return;
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
    B_000002E0[D_000002D4++] = c;
}
