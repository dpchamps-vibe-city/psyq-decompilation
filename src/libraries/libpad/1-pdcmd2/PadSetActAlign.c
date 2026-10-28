#include "common.h"
#include <libpad.h>
#include "libpad-internal.h"

static void func_000000E4(PadInfo2 *);
static int func_0000010C(PadInfo2 *);

int PadSetActAlign(int port, unsigned char *table) {
    PadInfo2 *info;

    info = _padFuncPort2Info(port);
    if (_padFuncChkEng(info) == 0) {
        info->commandState = 1;
        info->prepareCommand = func_000000E4;
        info->commandTable = table;
        info->applyResponse = func_0000010C;
        return 1;
    }
    return 0;
}
