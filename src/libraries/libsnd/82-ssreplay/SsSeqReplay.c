#include "common.h"
#include <libsnd.h>

void _SsSndSetReplayMode();       /* static */

void SsSeqReplay(short arg0) {
    _SsSndSetReplayMode(arg0, 0);
}
