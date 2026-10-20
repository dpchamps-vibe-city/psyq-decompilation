#include "common.h"
#include <libsnd.h>

void _SsSndSetPauseMode(); /* static */

void SsSeqPause(short arg0) {
    _SsSndSetPauseMode(arg0, 0);
}
