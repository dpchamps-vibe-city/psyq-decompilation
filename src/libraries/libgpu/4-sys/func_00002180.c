#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

s32 SetIntrMask(s32);
void DMACallback(int, void *);
s32 func_00002908();
s32 func_0000293C();
s32 func_00002430();

typedef struct {
    s32 func;
    s32 data;
    s32 arg;
    s32 buf[21];
} QEntry;

extern volatile QEntry _que[64];
extern volatile s32 _qin;
extern volatile s32 _qout;
extern s32 D_00003328;
extern s32 *D_00003300;
extern s32 *D_0000330C;
extern u8 GEnv;

static s32 func_00002180(s32 (*arg0)(s32 *, s32), s32 *arg1, s32 arg2, s32 arg3) {
    u8 *g;
    s32 i;

    func_00002908();
    while (((_qin + 1) & 0x3F) == _qout) {
        if (func_0000293C() != 0) {
            return -1;
        }
        func_00002430();
    }
    D_00003328 = SetIntrMask(0);
    g = (u8 *) &GEnv;
    *(s32 *) (g + 8) = 1;
    if ((g[1] == 0) ||
        ((_qin == _qout) && ((*(volatile s32 *) D_0000330C & 0x01000000) == 0) &&
         (*(s32 *) (g + 0xC) == 0))) {
        do {

        } while (!(*(volatile s32 *) D_00003300 & 0x04000000));
        arg0(arg1, arg3);
        SetIntrMask(D_00003328);
        return 0;
    }
    DMACallback(2, func_00002430);
    if (arg2 != 0) {
        for (i = 0; i < arg2 / 4; i++) {
            _que[_qin].buf[i] = arg1[i];
        }
        _que[_qin].data = (s32) &_que[_qin].buf;
    } else {
        _que[_qin].data = (s32) arg1;
    }
    _que[_qin].arg = arg3;
    _que[_qin].func = (s32) arg0;
    _qin = (_qin + 1) & 0x3F;
    SetIntrMask(D_00003328);
    func_00002430();
    return (_qin - _qout) & 0x3F;
}
