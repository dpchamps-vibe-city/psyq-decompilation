#include "common.h"

s32 CD_getsector();                                 /* extern */

s32 DsGetSector(void) {
    return CD_getsector() == 0;
}
