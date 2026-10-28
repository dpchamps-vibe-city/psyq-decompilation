#include "common.h"
#include <libpad.h>
#include "libpad-internal.h"

static void func_00000104(PadInfo2 *);
static int func_0000015C(PadInfo2 *);

int PadSetMainMode(int socket, int offs, int lock) {
    PadInfo2 *info;

    info = _padFuncPort2Info(socket);
    if (_padFuncChkEng(info) == 0) {
        info->commandState = 1;
        info->prepareCommand = func_00000104;
        info->mode = offs;
        info->lock = lock;
        info->applyResponse = func_0000015C;
        lock = (offs != info->prevMode);
        info->modeEqual = !lock;
        return 1;
    }
    return 0;
}
