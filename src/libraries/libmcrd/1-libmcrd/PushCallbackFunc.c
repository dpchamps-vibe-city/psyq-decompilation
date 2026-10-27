#include "common.h"
#include <libapi.h>
#include <libmcrd.h>

extern MemCB B_00001BD0;

void PushCallbackFunc(void) {
    B_00001BD0 = MemCardCallback(NULL);
}
