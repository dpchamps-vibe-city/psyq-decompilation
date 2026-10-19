/* D2_002.OBJ folded member */
#include "common.h"

s32 DS_status();

s32 DsStatus(void) {
    return DS_status() & 0xFF;
}
