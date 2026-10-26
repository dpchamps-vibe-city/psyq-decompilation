#include "common.h"
#include <sys/types.h>
#include <libgte.h>

void GsInitRstVtxMIMe(u_long *primtop, u_long *hp)
{
    typedef struct {
        u_long source;
        u_long destination;
        short reserved;
        short count;
    } ResetRange;
    typedef struct {
        short reserved;
        short count;
        ResetRange ranges[1];
    } ResetBlock;
    int i, j, k;
    int count;
    u_long *diff;
    SVECTOR *destination;
    SVECTOR *source;
    ResetBlock *block;
    ResetRange *range;

    primtop++;
    diff = (u_long *)hp[2];
    destination = (SVECTOR *)hp[3];
    source = (SVECTOR *)hp[4];
    count = *(unsigned short *)((u8 *)primtop + 2);
    for (i = 0; i < count; i++) {
        block = (ResetBlock *)(diff + primtop[i + 1]);
        for (j = 0; j < block->count; j++) {
            range = &block->ranges[j];
            for (k = 0; k < range->count; k++) {
                destination[range->destination + k] = source[range->source + k];
            }
        }
    }
}
