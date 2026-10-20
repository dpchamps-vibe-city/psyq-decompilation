#include "common.h"
#include <libsnd.h>

void _SsSndStop();                /* static */

void SsSepStop(short arg0, short arg1) {
    _SsSndStop(arg0, arg1);
}
