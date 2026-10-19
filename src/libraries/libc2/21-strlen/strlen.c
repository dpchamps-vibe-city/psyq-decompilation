/* Original TU: library-input/psyq/LIB/LIBC2.LIB[21] STRLEN.OBJ
 * sha256: 09c32e826d0419e49a27ac5ff27140db65207753faab6634b187ff861ac9c670
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strlen
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

u32 strlen(s8 *s) {
    u32 len = 0;

    if (s == 0) {
        return 0;
    }
    while (*s++) {
        len++;
    }
    return len;
}
