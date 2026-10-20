#include "common.h"
#include <sys/types.h>
#include <libds.h>

s32 DS_system_status();                            /* extern */

int DsSystemStatus(void) {
    s32 temp_v0;
    s32 var_v0;

    temp_v0 = DS_system_status(0);
    var_v0 = temp_v0;
    if (temp_v0 == 1) {
        var_v0 = temp_v0;
        if (DsQueueLen() > 0) {
            var_v0 = 2;
        }
    }
    return var_v0;
}
