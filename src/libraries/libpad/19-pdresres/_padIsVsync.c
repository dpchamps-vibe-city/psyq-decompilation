#include "common.h"
#include "libpad-internal.h"

extern volatile u32 *D_00001F6C;

s32 _padIsVsync(void) {
    if (!(D_00001F6C[1] & 1)) {
        return 0;
    }
    if (!(D_00001F6C[0] & 1)) {
        return 0;
    }
    if (_padFuncIntGun != 0) {
        _padFuncIntGun();
    }
    return 1;
}
