#include "common.h"
#include <sys/types.h>
#include <libcd.h>
#include <libds.h>

s32 CD_datasync();                                  /* extern */

int CdDataSync(int mode) {
    return CD_datasync();
}
