#include "common.h"
#include <libspu.h>

s32 _SpuIsInAllocateArea_();                     /* extern */
extern s32 _spu_rev_offsetaddr;
extern s32 _spu_rev_reserve_wa;

long SpuReserveReverbWorkArea(long on_off) {
    if ((on_off != 0) && (_SpuIsInAllocateArea_(_spu_rev_offsetaddr) == 0)) {
        _spu_rev_reserve_wa = 1;
        return 1;
    }
    _spu_rev_reserve_wa = 0;
    return 0;
}
