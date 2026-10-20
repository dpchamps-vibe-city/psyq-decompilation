#include "common.h"
#include <libsnd.h>

void _SsSndSetPauseMode(); /* static */

void SsSepPause(short arg0, short arg1) {
    _SsSndSetPauseMode(arg0, arg1);
}
