#include "86-free3.h"

void free3(void *arg0) {
    Block *p;
    Block *q;
    Block *nxt;

    if (arg0 == 0) {
        return;
    }
    p = (Block *)((u8 *)arg0 - 8);

    for (q = _freep; !(p > q && p < q->next); q = q->next) {
        if (q >= q->next && (p > q || p < q->next)) {
            break;
        }
    }
    _r_bp.bp = p;
    _r_bp.size = p->size;
    _r_bp.next = p->next;
    _r_p.bp = q;
    _r_p.size = q->size;
    _r_p.next = q->next;
    _r_freep = _freep;
    nxt = p + p->size;
    if (nxt == q->next && nxt->size != 0) {
        p->size += nxt->size;
        p->next = q->next->next;
    } else {
        p->next = q->next;
    }
    if (q + q->size == p) {
        q->size += p->size;
        q->next = p->next;
    } else {
        q->next = p;
    }
    _freep = q;
}
