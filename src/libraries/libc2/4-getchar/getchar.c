/* Folded from LIBC2.LIB[4] GETCHAR.OBJ. */
#include "common.h"
#include "library/3-getc.h"

s32 getchar(void) {
    u8 sp10;

    read(0, &sp10, 1);
    return sp10 & 0x7F;
}
