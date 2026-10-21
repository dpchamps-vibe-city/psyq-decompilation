#include "common.h"
#include <sys/types.h>
#include <libds.h>

int DsGetToc(DslLOC *loc) {
    u_char param[4];
    u_char result[8];
    int first, last, i, n;

    if (DsQueueLen() != 0) {
        DsFlush();
    }
    param[0] = 1;
    if (DsControlB(0x13, param, result) == 0) return 0;
    first = btoi(result[1]);
    last = btoi(result[2]);
    param[0] = 0;
    if (DsControlB(0x14, param, result) == 0) return 0;
    loc->minute = result[1];
    loc->second = result[2];
    loc->sector = 0;
    n = 1;
    for (i = first; i <= last; i++) {
        param[0] = itob(i);
        if (DsControlB(0x14, param, result) == 0) return 0;
        loc[n].minute = result[1];
        loc[n].second = result[2];
        loc[n].sector = 0;
        n++;
    }
    return n - 1;
}
