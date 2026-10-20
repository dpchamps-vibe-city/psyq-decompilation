#include "common.h"
#include <sys/types.h>
#include <libcd.h>

s32 CD_ready(s32, u8 *);                            /* extern */

s32 DS_ready(u8 *arg0) {
    return CD_ready(1, arg0);
}
