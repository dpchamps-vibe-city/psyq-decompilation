#include "common.h"
#include <sys/types.h>
#include <libcd.h>

s32 CD_sync();                                      /* extern */

int CdSync(int mode, u_char *result) {
    return CD_sync();
}
