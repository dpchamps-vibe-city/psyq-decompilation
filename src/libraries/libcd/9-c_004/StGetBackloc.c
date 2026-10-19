#include "common.h"
#include <sys/types.h>
#include <libcd.h>

extern CdlLOC B_00000170 __asm__("$LB_00000170");
extern u_long B_00000174 __asm__("$LB_00000174");
extern s32 StMode;

int StGetBackloc(CdlLOC *loc) {
    if (StMode != 0) {
        return -1;
    }
    CdIntToPos(CdPosToInt(&B_00000170) + 1, loc);
    return B_00000174;
}
