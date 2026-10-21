#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

s32 SetIntrMask(s32);
void DMACallback(int, void *);

extern s32 *D_00003300;
extern s32 *D_0000330C;
extern s32 D_00003200;
extern s32 D_00003204;
extern s32 D_0000332C;
extern u8 GEnv;

typedef struct {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
} GpuCb;

static s32 func_00002430(void) {
    volatile GpuCb *cb;
    s32 mask = 0x01000000;

    if (*(volatile s32 *) D_0000330C & mask) {
        return 1;
    }
    D_0000332C = SetIntrMask(0);
    if ((_qin != _qout) && !(*(volatile s32 *) D_0000330C & mask)) {
        s32 ready = 0x04000000;
        s32 lmask = 0x01000000;
        do {
            if ((((_qout + 1) & 0x3F) == _qin) && (D_00003204 == 0)) {
                DMACallback(2, 0);
            }
            if (!(*(volatile s32 *) D_00003300 & ready)) {
                s32 ready2 = 0x04000000;
                do {

                } while (!(*(volatile s32 *) D_00003300 & ready2));
            }
            ((void (*)(s32, s32)) _que[_qout].func)(_que[_qout].data, _que[_qout].arg);
            _qout = (_qout + 1) & 0x3F;
        } while ((_qin != _qout) && !(*(volatile s32 *) D_0000330C & lmask));
    }
    SetIntrMask(D_0000332C);
    if ((_qin == _qout) && !(*(volatile s32 *) D_0000330C & 0x01000000) &&
        (*(s32 *) ((u8 *) &D_00003200) != 0) &&
        (*(s32 *) ((u8 *) &D_00003200 + 4) != 0)) {
        cb = (volatile GpuCb *) ((u8 *) &D_00003200 - 8);
        cb->unk8 = 0;
        ((void (*)(void)) (*(s32 *) ((u8 *) &D_00003200 + 4)))();
    }
    return (_qin - _qout) & 0x3F;
}
