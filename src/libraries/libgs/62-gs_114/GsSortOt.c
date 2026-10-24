#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

GsOT *GsSortOt(GsOT *ot_src, GsOT *ot_dest) {
    GsOT_TAG *ptr = ot_src->org;
    u32 idx = ot_src->point - ot_dest->offset;
    GsOT_TAG *dst = ot_dest->org;
    GsOT_TAG *prev = ptr;
    GsOT_TAG *prev2 = ptr;
    GsOT_TAG *slot;

    if (ptr->p != 0xFFFFFF) {
        do {
            prev2 = prev;
            prev = ptr;
            ptr = (GsOT_TAG *) (ptr->p);
        } while (ptr->p != 0xFFFFFF);
    }
    slot = (GsOT_TAG *) ((u32) idx * 4 + (u32) dst);
    prev2->p = slot->p;
    slot->p = (unsigned) ot_src->tag;
    return ot_dest;
}
