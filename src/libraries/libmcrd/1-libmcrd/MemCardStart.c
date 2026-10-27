#include "common.h"
#include <libapi.h>
#include <libmcrd.h>

typedef struct {
    volatile long unk00;
    volatile long unk04;
    volatile long unk08;
    long unk0C;
    long unk10;
    long unk14;
    long unk18[11];
    MemCB callback;
    long unk48;
    long unk4C;
    volatile long unk50;
    volatile long unk54;
} McrdState;

extern void UserFuncInit(void);
extern void _card_start(void);
static void func_00001850(u8, u8 *, s32 *, s32 *);
extern void VSyncCallbacks(s32, void (*)(u8, u8 *, s32 *, s32 *));

void MemCardStart(void) {
    McrdState *mcrd = (McrdState *)&B_00001B78;

    mcrd->unk0C = 0;
    mcrd->callback = 0;
    UserFuncInit();
    mcrd->unk00 = 0;
    mcrd->unk04 = 0;
    mcrd->unk08 = 0;
    mcrd->unk54 = 0;
    mcrd->unk50 = mcrd->unk54;
    mcrd->unk14 = -1;
    mcrd->unk4C = 1;
    mcrd->unk48 = 1;
    _card_start();
    VSyncCallbacks(7, func_00001850);
}
