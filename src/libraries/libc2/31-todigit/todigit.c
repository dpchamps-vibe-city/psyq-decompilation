/* Original TU: library-input/psyq/LIB/LIBC2.LIB[31] TODIGIT.OBJ
 * sha256: f075f60c581cebcadadbe6bad2ea4c666cb6b80b0a5fae53c0e0b8dc42c68a5f
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: todigit
 */
#include "common.h"
#include "include_asm.h"

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
