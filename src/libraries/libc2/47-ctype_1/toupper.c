/* TOUPPER.OBJ from LIBC2.LIB */
#include "common.h"

extern char _ctype_[];

s8 toupper(s8 c) {
    if ((_ctype_ + 1)[(u8)c] & 2) {
        c -= 0x20;
    }
    return c;
}
