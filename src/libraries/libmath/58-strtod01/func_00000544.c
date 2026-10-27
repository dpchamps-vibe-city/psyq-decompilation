/* Original TU: library-input/psyq/LIB/LIBMATH.LIB[58] STRTOD01.OBJ */
#include "common.h"

extern char _ctype_[];

/* PSY-Q ctype.h isspace operation (vendor: (_ctype_+1)[(unsigned char)(c)]&_S,
   _S == 0x08). The vendor header's toupper/tolower declarations are omitted:
   this TU's strtod part already declares toupper with the s8 types the
   original code uses. */
#define isspace(c) ((_ctype_ + 1)[(u8)(c)] & 0x08)

s8 *func_00000544(s8 *nptr, int *sign)
{
    do {
    } while (isspace(*nptr++));
    nptr--;
    if (*nptr == '+') {
        nptr++;
    } else if (*nptr == '-') {
        *sign = 1;
        nptr++;
    }
    return nptr;
}
