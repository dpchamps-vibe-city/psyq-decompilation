#include "common.h"
#include <libapi.h>
#include <libcomb.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} CombState;

typedef struct {
    u8 pad[0xA];
    volatile u16 unkA;
} CombDev;

extern volatile CombState B_00001288;
extern CombDev *$LD_000011D8 __asm__("D_000011D8");

static s32 func_000000D4(s32 arg0, s32 arg1);

static s32 func_000000D4(s32 arg0, s32 arg1) {
    if (0) {
        void *p = (void *)func_000000D4;
        (void)p;
    }
    if (B_00001288.unk0 != 0) {
        return -1;
    }
    B_00001288.unk8 = arg1;
    B_00001288.unk4 = arg0;
    B_00001288.unk0 = 1;
    $LD_000011D8->unkA = (u16) ($LD_000011D8->unkA | 0x800);
    $LD_000011D8->unkA = (u16) ($LD_000011D8->unkA | 0x20);
    return 0;
}
