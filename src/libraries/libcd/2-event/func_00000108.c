#include "common.h"

s32 CD_init();                                      /* extern */
s32 CD_initvol();                                   /* extern */

static s32 func_00000108(void) __asm__("$Lfunc_00000108");

static s32 func_00000108(void) {
    if (CD_init() != 0) {
        return 0;
    }
    return CD_initvol() == 0;
}
