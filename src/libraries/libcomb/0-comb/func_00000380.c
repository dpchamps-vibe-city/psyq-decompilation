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
    s32 unkC;
} CombCmd;

typedef struct {
    u8 pad[0x4];
    volatile u16 unk4;
    u16 unk6;
    u16 unk8;
    volatile u16 unkA;
} CombDevReg;

extern volatile CombCmd B_00001278;

#define DEV ((CombDevReg *) D_000011D8)

static s32 func_00000380(s32 arg0, s32 arg1);

static s32 func_00000380(s32 arg0, s32 arg1) {
    if (0) {
        void *p = (void *)func_00000380;
        (void)p;
    }
    if (B_00001278.unk0 != 0) {
        return -1;
    }
    B_00001278.unk8 = arg1;
    B_00001278.unk4 = arg0;
    B_00001278.unk0 = 1;
    B_00001278.unkC = DEV->unk4 & 0x80;
    DEV->unkA = (u16) (DEV->unkA | 0x400);
    return 0;
}
