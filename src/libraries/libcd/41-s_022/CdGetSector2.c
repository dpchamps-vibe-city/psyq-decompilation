#include "common.h"

s32 CD_getsector2();                                /* extern */

s32 CdGetSector2(void) {
    return CD_getsector2() == 0;
}
