#include "common.h"
#include <libpad.h>
#include "libpad-internal.h"

int PadInfoAct(int port, int type, int act) {
    PadInfo2 *info = _padFuncPort2Info(port);
    u8 *entry;

    if (type < 0)
        return info->actAlignCount;
    if (type >= info->actAlignCount)
        return 0;
    entry = info->actAlignData + type * 5;

    switch (act) {
    case InfoActFunc:
        return entry[0];
    case InfoActSub:
        return entry[1];
    case InfoActSize:
        return entry[2];
    case InfoActCurr:
        return entry[3];
    case InfoActSign:
        return entry[4];
    }
    return 0;
}
