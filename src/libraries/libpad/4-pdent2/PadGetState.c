#include "common.h"
#include <libpad.h>
#include "libpad-internal.h"

int PadGetState(int port) {
    PadInfo2 *info = _padFuncPort2Info(port);

    if (info->requestCommand != 0 || info->currentCommand != 0
        || (info != info->root && info->previousCommand != 0)
        || info->commandBuffer[0] != 0) {
        switch (info->state) {
        case PadStateFindCTP1:
            return PadStateFindPad;
        case PadStateFindCTP2:
            return PadStateFindPad;
        case PadStateStable:
            return PadStateReqInfo;
        }
    }
    return info->state;
}
