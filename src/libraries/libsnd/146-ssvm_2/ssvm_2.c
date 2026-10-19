/* Original TU: LIBSND.LIB[146] SSVM_2.OBJ */
#include "common.h"

extern s32 _snd_vmask;

s32 SsGetVoiceMask(void) {
    return _snd_vmask;
}
