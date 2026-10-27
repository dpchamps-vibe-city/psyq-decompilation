#include "common.h"
#include <libapi.h>
#include <libmcrd.h>

void MemCardClose(void)
{
    long *fd = &((McrdState *)&B_00001B78)->unk14;

    if (*fd >= 0) {
        close(*fd);
        *fd = -1;
    }
}
