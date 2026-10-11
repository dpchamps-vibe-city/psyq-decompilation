#include "common.h"

s32 DS_status();                                    /* extern */

s32 DsStatus(void) {
    return DS_status() & 0xFF;
}
