#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

GsCOORDUNIT *GsMapCoordUnit(u_long *base, u_long *top)
{
    u_long *headp;
    GsCOORDUNIT *coord;
    GsCOORDUNIT **superp;
    s32 num;
    s32 i;

    headp = GsGetHeadpUnit();
    coord = (GsCOORDUNIT *)headp[*headp];
    *headp = *headp - 1;
    num = *(s32 *)coord;
    coord = (GsCOORDUNIT *)((s32 *)coord + 1);
    i = 0;
    if (num > 0) {
        superp = &coord->super;
        do {
            if (*superp != 0) {
                *superp = (GsCOORDUNIT *)(base + (u_long)*superp);
            }
            i++;
            superp = (GsCOORDUNIT **)((char *)superp + 0x50);
        } while (i < num);
    }
    return coord;
}
