/* Original TU: library-input/psyq/LIB/LIBAPI.LIB[87] REALLOC3.OBJ
 * sha256: 6595d4a8bc791b75ef95489f78142eed07fc3007e17e8742d009a54d105f928a
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: realloc3
 */
#include "common.h"
#include "include_asm.h"

#include "86-free3.h"
#include <malloc.h>
static void func_0000014C(void);
static void *func_000001A0(void *, void *, s32);

void *realloc3(void *ptr, u32 size) {
    Block *bp;
    Block *tail;
    void *result;
    s32 old_units;
    u32 rounded_units;
    s32 new_units;
    s32 copy_bytes;

    if (ptr == 0) {
        return malloc3(size);
    }
    if (size == 0) {
        free3(ptr);
        return 0;
    }
    rounded_units = (size + 7) >> 3;
    /* Keep header formation separate from the subsequent field accesses. */
    do {
        bp = (Block *)((u8 *)ptr - 8);
    } while (0);
    old_units = bp->size;
    new_units = rounded_units + 1;
    copy_bytes = (old_units - 1) * 8;
    if (old_units != new_units) {
        if (old_units < new_units) {
            free3(ptr);
            result = malloc3(size);
            if (result == 0) {
                func_0000014C();
                return 0;
            }
            func_000001A0(result, ptr, copy_bytes);
            return result;
        }
        tail = bp + new_units;
        tail->size = old_units - new_units;
        bp->size = new_units;
        free3(tail + 1);
    }
    return ptr;
}
#include "86-free3.h"

static void func_0000014C(void) {
    Block *bp;

    bp = _r_p.bp;
    bp->size = _r_p.size;
    bp->next = _r_p.next;
    bp = _r_bp.bp;
    bp->size = _r_bp.size;
    _freep = _r_freep;
    bp->next = _r_bp.next;
}
#include "common.h"

static void *func_000001A0(void *dest, void *source, s32 count) {
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
