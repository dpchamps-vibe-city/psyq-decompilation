/* Original TU: LIBSND.LIB SSGM.OBJ */
#include "common.h"

s32 SpuGetMute();                                   /* extern */

s32 SsGetMute(void) {
    return SpuGetMute() != 0;
}
