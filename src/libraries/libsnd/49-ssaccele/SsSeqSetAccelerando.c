#include "common.h"
#include <libsnd.h>

void _SsSndSetAccele(s16 arg0, s16 arg1, s32 arg2, s32 arg3); /* static */

void SsSeqSetAccelerando(short arg0, long arg1, long arg2) {
    _SsSndSetAccele(arg0, 0, arg1, arg2);
}
