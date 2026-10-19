/* Original TU: library-input/psyq/LIB/LIBC2.LIB[30] STRTOUL.OBJ */
#include "common.h"

extern u32 todigit(s8);
extern s8 toupper(s8);
extern char _ctype_[];

#define isspace(c) ((_ctype_ + 1)[(unsigned char)(c)] & 8)

unsigned long strtoul(const s8 *nptr, char **endptr, u32 base_param) {
    unsigned long acc;
    u32 base;
    s8 c;
    u32 digit;

    base = base_param;
    acc = 0;
    if (nptr == 0)
        return 0;
    do {
    } while (isspace(*nptr++));
    nptr--;
    if (base - 2 >= 0x23U)
        base = 0;
    if (base == 0)
        base = 10;
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
        }
    } else if (toupper(*nptr) == 'O') {
        nptr++;
        base = 8;
    }
    while ((digit = todigit(*nptr++)) < base) {
        acc = acc * base;
        acc = acc + digit;
    }
    if (endptr != 0)
        *endptr = (char *)--nptr;
    return acc;
}
