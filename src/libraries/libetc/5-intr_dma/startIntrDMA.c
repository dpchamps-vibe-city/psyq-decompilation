#include "common.h"

typedef void (*DMAFunc)(void);
typedef DMAFunc (*DMAHandler)(s32, DMAFunc);

static void func_000000C4(void);
static DMAFunc func_00000244(s32, DMAFunc);
static void func_000002F0(DMAFunc *, s32);
extern s32 InterruptCallback(s32, DMAFunc);
extern DMAFunc D_0000034C[8];
extern s32 *D_00000348;

DMAHandler startIntrDMA(void) {
    func_000002F0(D_0000034C, 8);
    *D_00000348 = 0;
    InterruptCallback(3, func_000000C4);
    return func_00000244;
}
