#include "common.h"

extern s32 $LD_000002D0;
extern s32 $LD_000002D4;
extern s8 $LB_000002E0[];

void _putchar_flash(void) {
    if ($LD_000002D4 > 0) {
        write(1, $LB_000002E0, $LD_000002D4);
        $LD_000002D4 = 0;
    }
}
