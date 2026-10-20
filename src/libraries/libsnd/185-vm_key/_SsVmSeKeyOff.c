#include "common.h"
#include <libsnd.h>

s32 _SsVmKeyOff(s16 arg0, s16 arg1, s16 arg2, s32 arg3); /* static */

s32 _SsVmSeKeyOff(s16 arg0, s16 arg1, s32 arg2) {
    return _SsVmKeyOff(0x21, arg0, arg1, arg2 & 0xFFFF);
}
