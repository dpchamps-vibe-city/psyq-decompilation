#include "common.h"
#include <sys/types.h>
#include <libds.h>

int DsControlB(u_char com, u_char*param, u_char*result) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0_2 = DsCommand(com & 0xFF, param, NULL, 0);
    if (temp_v0_2 == 0) {
        return 0;
    }
    do {
        temp_v0 = DsSync(temp_v0_2, result) & 0xFF;
    } while (temp_v0 == 0);
    return temp_v0 == 2;
}
