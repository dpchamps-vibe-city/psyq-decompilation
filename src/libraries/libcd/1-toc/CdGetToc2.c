#include "common.h"
#include <sys/types.h>
#include <stdio.h>
#include <libcd.h>

int CdGetToc2(int mode, CdlLOC *loc) {
    u_char param[4];
    u_char result[8];
    CdlCB oldcb;
    int first, last, i, n, last_idx;

    param[0] = 1;
    oldcb = CdSyncCallback(0);
    if (CdControlB(CdlGetTN, 0, result) == 0) goto error;
    first = btoi(result[1]);
    last = btoi(result[2]);
    if (CD_debug >= 2) printf("track=%d,%d\n", first, last);
    param[0] = 0;
    if (CdControlB(CdlGetTD, param, result) == 0) goto error;
    loc->minute = result[1];
    loc->second = result[2];
    loc->sector = 0;
    n = 1;
    if (first <= last) {
        i = first;
        do {
            param[0] = itob(i);
            if (CdControlB(CdlGetTD, param, result) == 0) goto error;
            loc[n].minute = result[1];
            loc[n].second = result[2];
            loc[n].sector = 0;
            n++;
            i++;
        } while (i <= last);
    }
    last_idx = n - 1;
    if (CD_debug >= 2) {
        for (n = 0; n <= last_idx; n++)
            printf("CdGetToc2: %02x:%02x:00\n", loc[n].minute, loc[n].second);
    }
    CdSyncCallback(oldcb);
    return last_idx;
error:
    if (CD_debug) printf("CdGetToc2: error\n");
    CdSyncCallback(oldcb);
    return 0;
}
