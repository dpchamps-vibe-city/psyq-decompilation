/* TOLOWER.OBJ from LIBC2.LIB */
#include "common.h"

extern char _ctype_[];

s8 tolower(s8 c) {
    if ((_ctype_ + 1)[(u8)c] & 1) {
        c += 0x20;
    }
    return c;
}
