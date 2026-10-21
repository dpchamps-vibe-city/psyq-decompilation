#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <strings.h>

extern u16 B_00005B48;
extern u16 B_00005B4A;
extern s32 D_00000D30;
extern u_long D_00000D38[];
extern u_long Font[];

void FntLoad(int tx, int ty) {
    B_00005B4A = LoadClut2(&D_00000D38[0], tx, ty + 0x80);
    B_00005B48 = LoadTPage(&D_00000D38[0x80], 0, 0, tx, ty, 0x80, 0x20);
    D_00000D30 = 0;
    memset(Font, 0, 0x180);
}
