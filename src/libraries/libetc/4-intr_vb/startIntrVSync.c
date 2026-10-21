#include "common.h"

typedef void (*VBlankFunc)(void);

void func_000000C8(void);
void func_00000134(s32, VBlankFunc);
void func_00000160(VBlankFunc *, s32);
extern s32 InterruptCallback(s32, VBlankFunc);
extern VBlankFunc D_00000190[8];
extern s32 Vcount;
extern s32 *D_000001B4;

void (*startIntrVSync(void))(s32, VBlankFunc) {
    *D_000001B4 = 0x100;
    Vcount = 0;
    func_00000160(D_00000190, 8);
    InterruptCallback(0, func_000000C8);
    return func_00000134;
}
