/* TODIGIT.OBJ from LIBC2.LIB */
#include "common.h"

extern s8 tolower(s8);
extern char _ctype_[];

#define isdigit(c) ((_ctype_ + 1)[(unsigned char)(c)] & 4)
#define isalpha(c) ((_ctype_ + 1)[(unsigned char)(c)] & 3)

s32 todigit(s8 c) {
    if (isdigit(c)) {
        return c - 0x30;
    }
    /* PSYQ returns 0x98967F (9999999) for non-alphanumeric, not -1. */
    return isalpha(c) ? tolower(c) - 0x57 : 0x98967F;
}
