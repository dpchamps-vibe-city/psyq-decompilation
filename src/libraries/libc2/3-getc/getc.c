/* Original TU: library-input/psyq/LIB/LIBC2.LIB[3] GETC.OBJ
 * sha256: bbf435ef09ec58ebe8dd5d297becbe067905bdc278455115ab1e720c17470dab
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: getc
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"
#include "library/3-getc.h"

s8 getc(s32 fd) {
    s8 c;

    if (read(fd, &c, 1) > 0) {
        return c;
    }
    return -1;
}
