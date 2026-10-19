#include "common.h"
#include "library/11-putc.h"
#include <ctype.h>

extern s32 $LD_000002D0;
extern s32 $LD_000002D4;
extern s8 $LB_000002E0[];

void _putchar(s8 c) {
    switch (c) {
    case '\n':
        _putchar('\r');
        $LD_000002D0 = 0;
        break;
    case '\t':
        do {
            _putchar(' ');
        } while ($LD_000002D0 & 7);
        return;
    default:
        if ((((signed char *)(_ctype_ + 1))[(unsigned char)(c)] & 0x97)) {
            $LD_000002D0++;
        }
        break;
    }
    if ($LD_000002D4 >= 0x20) {
        write(1, $LB_000002E0, $LD_000002D4);
        $LD_000002D4 = 0;
    }
    $LB_000002E0[$LD_000002D4++] = c;
}
