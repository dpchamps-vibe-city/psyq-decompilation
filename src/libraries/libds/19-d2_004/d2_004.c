/* Original TU: LIBDS.LIB[19] D2_004.OBJ */
#include "common.h"

s32 DS_lastcom();

s32 DsLastCom(void)
{
    return DS_lastcom() & 0xFF;
}
