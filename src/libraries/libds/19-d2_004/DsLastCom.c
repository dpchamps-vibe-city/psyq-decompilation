#include "common.h"

s32 DS_lastcom();                                   /* extern */

s32 DsLastCom(void) {
    return DS_lastcom() & 0xFF;
}
