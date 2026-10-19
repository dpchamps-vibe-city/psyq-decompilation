/* LIBDS.LIB D3_003.OBJ */
#include "common.h"

s32 CD_getsector2();                                /* extern */

s32 DsGetSector2(void) {
    return CD_getsector2() == 0;
}
