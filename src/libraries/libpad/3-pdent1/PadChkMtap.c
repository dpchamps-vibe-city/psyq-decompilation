#include "common.h"
#include "libpad-internal.h"

int PadChkMtap(int port) {
    if (_padModeMtap != 0) {
        return _padInfoDir[port >> 4].mtapType == 8;
    }
    return 0;
}
