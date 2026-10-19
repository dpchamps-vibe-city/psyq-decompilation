/* Folded from LIBC2.LIB[3] GETC.OBJ. */
#include "common.h"
#include "library/3-getc.h"

s8 getc(s32 fd) {
    s8 c;

    if (read(fd, &c, 1) > 0) {
        return c;
    }
    return -1;
}
