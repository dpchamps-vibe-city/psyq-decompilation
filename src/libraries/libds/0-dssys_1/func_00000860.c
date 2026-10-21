#include "common.h"

extern void CD_flush(void);
extern s32 CD_cw(s32 com, u8 *param, u8 *result, s32 mode);

static s32 func_00000860(void) {
    s32 t;

    CD_flush();
    D_00001240.unk48++;
    D_00001240.timeout = (t = D_00001294[D_00001240.command]) ? t * 0x3C : 0x1E;
    CD_cw(D_00001240.command, D_00001240.param_ptr, 0, 1);
    return 0;
}
