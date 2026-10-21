#include "common.h"

extern DsSystem LD_00001258 __asm__("D_00001258");
static s32 func_000003B8(u8, u8 *);

s32 DS_cw_system(u8 com, u8 *param) {
    if (LD_00001258.unk2C > 0) {
        return 0;
    }
    LD_00001258.unk4 = 0x20;
    return func_000003B8(com, param);
}
