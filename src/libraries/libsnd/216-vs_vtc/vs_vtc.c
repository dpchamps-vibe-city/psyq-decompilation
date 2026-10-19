/* Original TU: library-input/psyq/LIB/LIBSND.LIB[216] VS_VTC.OBJ */
#include "common.h"

s16 SpuIsTransferCompleted(s16);                    /* extern */

s16 SsVabTransCompleted(s16 vab_id) {
    return SpuIsTransferCompleted(vab_id);
}
