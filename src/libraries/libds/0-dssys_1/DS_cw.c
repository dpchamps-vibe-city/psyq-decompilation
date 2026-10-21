#include "common.h"

typedef struct {
    s32 active;
    u8 pad0[0x18];
    s32 f1C;
    s32 f20;
    s32 f24;
    u8 pad1[0x1C];
    s32 f44;
} DsSys;

extern DsSys D_00001240;
static s32 func_000003B8(u8, u8 *);

s32 DS_cw(u8 com, u8 *param) {
    if (D_00001240.f44 > 0) {
        return 0;
    }
    if (D_00001240.active == 0) {
        return 0;
    }
    if (D_00001240.f20 != 1) {
        return 0;
    }
    D_00001240.f1C = 0x1F;
    D_00001240.f20 = 2;
    D_00001240.f24 = 0xB;
    return func_000003B8(com, param);
}
