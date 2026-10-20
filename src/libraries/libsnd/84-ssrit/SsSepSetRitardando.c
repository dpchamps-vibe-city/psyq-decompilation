#include "common.h"
#include <libsnd.h>

void _SsSndSetRit(s16 arg0, s16 arg1, s32 arg2, s32 arg3); /* static */

void SsSepSetRitardando(short arg0, short arg1, long arg2, long arg3) {
    _SsSndSetRit(arg0, arg1, arg2, arg3);
}
