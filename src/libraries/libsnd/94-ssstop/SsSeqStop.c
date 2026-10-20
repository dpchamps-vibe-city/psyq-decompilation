#include "common.h"
#include <libsnd.h>

void _SsSndStop();                /* static */

void SsSeqStop(short arg0) {
    _SsSndStop(arg0, 0);
}
