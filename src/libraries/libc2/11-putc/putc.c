/* Original TU: library-input/psyq/LIB/LIBC2.LIB[11] PUTC.OBJ
 * sha256: 7f2c4b2a15ea2636528e6d61fd83b35cedc167f93fa880ab7df7ebb820b3b07d
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: putc
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"
#include "library/11-putc.h"

void putc(s8 c, long fd) {
    write(fd, &c, 1);
}
