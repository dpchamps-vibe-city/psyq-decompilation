/* library-input/psyq/LIB/LIBAPI.LIB[88] CALLOC3.OBJ */
#include "common.h"

u32 malloc3(s32);                                   /* extern */
static void zero_memory(u8 *dest, s32 len);

u32 calloc3(s32 count, s32 size) {
    s32 total_size;
    u32 ptr;

    total_size = size * count;
    ptr = malloc3(total_size);
    if (ptr == 0) {
        return 0U;
    }
    zero_memory((u8 *)ptr, total_size);
    return ptr;
}
static void zero_memory(u8 *dest, s32 len) {
    u8 *end;
    u8 *p;

    p = dest;
    end = p + len;
    if (p < end) {
        do {
            *p = 0;
            p += 1;
        } while (p < end);
    }
}
