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
