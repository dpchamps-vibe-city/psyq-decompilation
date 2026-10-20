#include "common.h"
#include <sys/types.h>
#include <libcd.h>

s32 CD_ready();                                     /* extern */

int CdReady(int mode, u_char *result) {
    return CD_ready();
}
