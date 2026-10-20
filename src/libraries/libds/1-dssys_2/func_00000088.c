#include "common.h"

typedef struct {
    s32 active;
    u8 command;
    u8 param[4];
    u8 pad[3];
    s32 unkC;
    s32 unk10;
    s32 unk14;
} DsCommand;

static void func_00000088(DsCommand *p) __asm__("$Lfunc_00000088");

static void func_00000088(DsCommand *p) {
    s32 i;
    u8 *q;
    void (*self)(DsCommand *);

    self = func_00000088;
    (void) self;
    p->active = 0;
    p->command = 0;
    i = 3;
    q = (u8 *) p + 3;
    do {
        q[5] = 0;
        i--;
        q--;
    } while (i >= 0);
    p->unkC = 0;
    p->unk10 = 0;
    p->unk14 = 0;
}
