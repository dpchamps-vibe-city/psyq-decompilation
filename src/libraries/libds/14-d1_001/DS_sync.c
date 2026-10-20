#include "common.h"
#include <sys/types.h>
#include <libcd.h>

s32 CD_sync(s32, u8 *);                             /* extern */

s32 DS_sync(u8 *arg0) {
    return CD_sync(1, arg0);
}
