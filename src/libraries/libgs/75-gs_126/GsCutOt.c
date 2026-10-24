#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

GsOT *GsCutOt(GsOT *ot_src, GsOT *ot_dest) {
    GsOT_TAG *tag = ot_src->tag;
    GsOT_TAG *prev = tag;
    GsOT_TAG *first;
    int flag = 1;
    u32 t;

    while (1) {
        t = (u32)tag & 0xFFFFFF;
        if (t == 0xFFFFFF) {
            *(u32 *)prev |= t;
            break;
        }
        if (tag->num == 0) {
            tag = (GsOT_TAG *) ((u32)tag->p | 0x80000000);
        } else {
            if (flag) {
                first = tag;
                flag = 0;
            }
            *(u32 *)prev = (*(u32 *)prev & 0xFF000000) | t;
            prev = tag;
            tag = (GsOT_TAG *) ((u32)tag->p | 0x80000000);
        }
    }
    ot_dest->length = 0;
    ot_dest->org = NULL;
    if (flag) {
        ot_dest->tag = (GsOT_TAG *)0xFFFFFF;
        return NULL;
    }
    ot_dest->tag = first;
    return ot_dest;
}
