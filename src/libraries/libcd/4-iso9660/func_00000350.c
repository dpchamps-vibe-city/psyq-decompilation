#include "common.h"

s32 strncmp(s8 *s1, s8 *s2, s32 n);

static s32 func_00000350(s8 *s1, s8 *s2) __asm__("$Lfunc_00000350");

static s32 func_00000350(s8 *s1, s8 *s2) {
    if (0) {
        func_00000350(s1, s2);
    }
    return strncmp(s1, s2, 12) == 0;
}
