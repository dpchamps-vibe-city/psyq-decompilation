#include "common.h"
#include <libpad.h>
#include "libpad-internal.h"

int PadInfoMode(int port, int infoMode, int infoId) {
    PadInfo2 *info = _padFuncPort2Info(port);

    switch (infoMode) {
    case InfoModeCurID:
        return info->mtapType;
    case InfoModeCurExID:
        return info->exId;
    case InfoModeCurExOffs:
        return info->prevMode;
    case InfoModeIdTable:
        if (infoId < 0) {
            return info->idCount;
        }
        if (infoId < info->idCount) {
            return info->idTable[infoId];
        }
        return 0;
    case 100:
        return info->unk4C;
    default:
        return 0;
    }
}
