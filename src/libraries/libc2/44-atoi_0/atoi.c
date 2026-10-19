#include "common.h"

extern u32 todigit(s8);
extern char _ctype_[];

#define isspace(c) ((_ctype_ + 1)[(unsigned char)(c)] & 8)

s32 atoi(const s8 *nptr) {
    s32 n;
    s32 sign;
    u32 base;
    u32 digit;
    s8 c;

    sign = 1;
    base = 10;
    n = 0;
    if (nptr == 0)
        return 0;
    do {
    } while (isspace(*nptr++));
    nptr--;
    if (*nptr == '-') {
        do {
            nptr++;
            sign = -sign;
        } while (*nptr == '-');
    }
    if (*nptr == '0') {
        c = *++nptr;
        switch (c) {
        case 'x':
        case 'X':
            nptr++;
            base = 16;
            break;
        case 'b':
        case 'B':
            nptr++;
            base = 2;
            break;
        default:
            base = 8;
            break;
        }
    }
    while ((digit = todigit(*nptr++)) < base) {
        n = n * base;
        n = n + digit;
    }
    return n * sign;
}
