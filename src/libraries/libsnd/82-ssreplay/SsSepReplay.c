#include "common.h"
#include <libsnd.h>

void _SsSndSetReplayMode();       /* static */

void SsSepReplay(short arg0, short arg1) {
    _SsSndSetReplayMode(arg0, arg1);
}
