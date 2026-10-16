#include "common.h"

/* PAD.OBJ .data+8: pointer to MMIO 0x1F801070; +0 is the interrupt status
 * word and +4 the interrupt mask word. Storage remains in _data.c; this
 * declaration supplies its source type. */
extern u32 *D_00000308;

static s32 func_000002BC(void) {
    if (D_00000308[1] & 1) {
        if (D_00000308[0] & 1) {
            goto ret_one;
        }
    }
    return 0;
ret_one:
    return 1;
}
