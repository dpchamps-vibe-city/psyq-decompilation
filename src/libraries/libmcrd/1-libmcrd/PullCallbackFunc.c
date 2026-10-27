#include "common.h"
#include <libmcrd.h>

extern MemCB B_00001BD0;

MemCB PullCallbackFunc(void) {
    return MemCardCallback(B_00001BD0);
}
