#include "common.h"

extern void CD_flush(void);
extern s32 CD_cw(s32 com, u8 *param, u8 *result, s32 mode);

s32 func_00000860(void) {
    s32 t;

    CD_flush();
    D_00001240r.unk44++;
    D_00001240r.timeout = (t = D_00001294[D_00001240r.command]) ? t * 0x3C : 0x1E;
    CD_cw(D_00001240r.command, D_00001240r.param_ptr, 0, 1);
    return 0;
}
