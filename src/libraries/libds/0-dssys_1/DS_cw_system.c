#include "common.h"

static s32 func_000003B8(u8, u8 *);

s32 DS_cw_system(u8 com, u8 *param) {
    if (D_00001240.timeout > 0) {
        return 0;
    }
    D_00001240.unk1C = 0x20;
    return func_000003B8(com, param);
}
