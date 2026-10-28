#include "common.h"
#include "libpad-internal.h"

static void func_000014C4(PadInfo2 *);
static void func_000014D8(PadInfo2 *, u8);
static void func_00001518(PadInfo2 *, u8);

void _padSendAtLoadInfo(PadInfo2 *arg0) {
    switch (arg0->commandState) {
    case 2:
        func_000014C4(arg0);
        break;
    case 3:
        func_000014D8(arg0, arg0->prevMode);
        break;
    case 4:
        func_00001518(arg0, arg0->pad47[0]);
        break;
    }
}
