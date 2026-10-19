/* Original TU: library-input/psyq/LIB/LIBC.LIB[55] STRTOL.OBJ
 * sha256: 5b00a79584d533fd211694bb0b5c778f98a116a311fdf53ab502baa20b68eef1
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strtol
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

extern u32 todigit(s8);
extern s8 toupper(s8);
extern char _ctype_[];

#define isspace(c) ((_ctype_ + 1)[(unsigned char)(c)] & 8)

long strtol(const s8 *arg0, char **arg1, u32 arg2) {
    long acc;
    s32 base;
    s32 sign;
    s8 c;
    s32 digit;

    base = arg2;
    sign = 1;
    acc = 0;
    if (arg0 == 0)
        return 0;
    do {
    } while (isspace(*arg0++));
    arg0--;
    while (*arg0 == '-') {
        arg0++;
        sign = -sign;
    }
    if (base - 2 >= 0x23U)
        base = 0;
    if (base == 0)
        base = 10;
    if (*arg0 == '0') {
        c = *++arg0;
        switch (c) {
        case 'x':
        case 'X':
            arg0++;
            base = 16;
            break;
        case 'b':
        case 'B':
            arg0++;
            base = 2;
            break;
        }
    } else if (toupper(*arg0) == 'O') {
        arg0++;
        base = 8;
    }
    while ((digit = todigit(*arg0++)) < base) {
        acc = acc * base;
        acc = acc + digit;
    }
    if (arg1 != 0)
        *arg1 = (char *)--arg0;
    return acc * sign;
}
