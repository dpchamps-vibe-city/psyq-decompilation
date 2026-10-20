#include "common.h"
#include <sys/types.h>
#include <libcd.h>
#include <libetc.h>

int CdDiskReady(int mode) {
    u8 result;
    u8 r;
    int status;
    int retry;
    int ready;

    CdControlB(1, 0, &result);
    if (result & 0x10) {
        return 0x10;
    }
    status = CdControlB(0x13, 0, &result);
    if (mode == 1) {
        if (result != 2) {
            goto fail;
        }
        if (status != 0) {
            return 2;
        }
        return 5;
    }
    ready = 2;
    for (retry = 0; retry < 10; retry++) {
        if ((r = result) & 2) {
            if (r == ready && status != 0) {
                return 2;
            }
            do {
                VSync(0x1E);
                status = CdControlB(0x13, 0, &result);
                r = result;
                if (r & 0x10) {
                    return 0x10;
                }
            } while (r != ready || status == 0);
            return 2;
        }
        VSync(0x1E);
        status = CdControlB(0x13, 0, &result);
        if (result & 0x10) {
            return 0x10;
        }
    }
fail:
    return 5;
}
