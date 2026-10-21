#include "common.h"

static s32 func_000003B8(u8, u8 *);

s32 DS_cw(u8 com, u8 *param) {
    if (D_00001240.timeout > 0) {
        return 0;
    }
    if (D_00001240.active == 0) {
        return 0;
    }
    if (D_00001240.system[0] != 1) {
        return 0;
    }
    D_00001240.unk1C = 0x1F;
    D_00001240.system[0] = 2;
    D_00001240.system[1] = 0xB;
    return func_000003B8(com, param);
}
