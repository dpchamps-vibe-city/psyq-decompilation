#include "common.h"
#include <sys/types.h>
#include <libds.h>

int DsSetDebug(int level) {
    s32 temp_v0;

    temp_v0 = CD_debug;
    CD_debug = level;
    return temp_v0;
}
