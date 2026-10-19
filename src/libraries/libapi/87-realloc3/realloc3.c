/* REALLOC3.OBJ: realloc3 */
#include "86-free3.h"
#include <malloc.h>
static void restore_reserve(void);
static void *copy_bytes(void *, void *, s32);

void *realloc3(void *ptr, u32 size) {
    Block *bp;
    Block *tail;
    void *result;
    s32 old_units;
    u32 rounded_units;
    s32 new_units;
    s32 copy_len;

    if (ptr == 0) {
        return malloc3(size);
    }
    if (size == 0) {
        free3(ptr);
        return 0;
    }
    rounded_units = (size + 7) >> 3;

    do {
        bp = (Block *)((u8 *)ptr - 8);
    } while (0);
    old_units = bp->size;
    new_units = rounded_units + 1;
    copy_len = (old_units - 1) * 8;
    if (old_units != new_units) {
        if (old_units < new_units) {
            free3(ptr);
            result = malloc3(size);
            if (result == 0) {
                restore_reserve();
                return 0;
            }
            copy_bytes(result, ptr, copy_len);
            return result;
        }
        tail = bp + new_units;
        tail->size = old_units - new_units;
        bp->size = new_units;
        free3(tail + 1);
    }
    return ptr;
}

static void restore_reserve(void) {
    Block *bp;

    bp = _r_p.bp;
    bp->size = _r_p.size;
    bp->next = _r_p.next;
    bp = _r_bp.bp;
    bp->size = _r_bp.size;
    _freep = _r_freep;
    bp->next = _r_bp.next;
}

static void *copy_bytes(void *dest, void *source, s32 count) {
    u8 *d;
    u8 *s;

    d = dest;
    s = source;
    if (d >= s) {
        if (count--) {
backward_body:
            d[count] = s[count];
            if (count--) {
                goto backward_body;
            }
        }
    } else {
        if (count--) {
forward_body:
            *d++ = *s++;
            if (count--) {
                goto forward_body;
            }
        }
    }
    return dest;
}
