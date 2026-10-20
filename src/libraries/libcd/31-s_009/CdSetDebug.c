#include "common.h"
#include <sys/types.h>
#include <libcd.h>

int CdSetDebug(int level) {
    s32 temp_v0;

    temp_v0 = CD_debug;
    CD_debug = level;
    return temp_v0;
}
