#include "common.h"

extern s8 tolower(s8);
extern char _ctype_[];

#define isdigit(c) ((_ctype_ + 1)[(unsigned char)(c)] & 4)
#define isalpha(c) ((_ctype_ + 1)[(unsigned char)(c)] & 3)

s32 todigit(s8 arg0) {
    if (isdigit(arg0)) {
        return arg0 - 0x30;
    }
    return isalpha(arg0) ? tolower(arg0) - 0x57 : 0x98967F;
}
