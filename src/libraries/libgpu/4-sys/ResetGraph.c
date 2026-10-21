#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern u8 GEnv;
extern u32 D_000031B0;
extern u32 D_00003278[];
extern u32 D_00003284[];
extern char RO_STR_00002FC0[];
extern char RO_STR_00002FE0[];

typedef struct {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u32 unk10;
    u32 unk14;
    u32 unk18;
    u32 unk1C;
    u32 unk20;
    u32 unk24;
    u32 unk28;
    u32 unk2C;
    u32 unk30;
    int (*unk34)(int);
} GpuDispatch;

extern GpuDispatch *D_000031F0;
extern void GPU_cw(u32 cmd);
extern int func_00002690(int mode);
extern void func_00002F60(u8 *p, int c, int n);

int ResetGraph(int mode) {
    u8 *p;

    switch (mode & 7) {
    case 3:
    case 0:
        printf(RO_STR_00002FC0, &D_000031B0, &GEnv);
    case 5:
        p = &GEnv;
        func_00002F60(p, 0, 0x80);
        ResetCallback();
        GPU_cw((u32) D_000031F0 & 0xFFFFFF);
        p[0] = func_00002690(mode);
        p[1] = 1;
        *(u16 *) (p + 4) = *(u16 *) &D_00003278[p[0]];
        *(u16 *) (p + 6) = *(u16 *) &D_00003284[p[0]];
        func_00002F60(p + 0x10, -1, 0x5C);
        func_00002F60(p + 0x6C, -1, 0x14);
        return p[0];
    default:
        if (((u8 *) &GEnv)[2] >= 2) {
            GPU_printf(RO_STR_00002FE0, mode);
        }
        return D_000031F0->unk34(1);
    }
}
