#include "86-free3.h"

static void func_0000014C(void) {
    BlockReg *r;
    Block *bp;

    r = &_r_p;
    bp = r->bp;
    bp->size = r->size;
    bp->next = r->next;

    r = &_r_bp;
    bp = r->bp;
    bp->size = r->size;
    _freep = _r_freep;
    bp->next = r->next;
}
