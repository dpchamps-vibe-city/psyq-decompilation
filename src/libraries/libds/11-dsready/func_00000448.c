#include "common.h"

void func_00000448(u_char arg0, u_char *arg1, u_long *arg2) {
    if ((D_00000610.mode != 0) && (D_00000610.active != 0)) {
        if ((arg0 & 0xFF) == 2) {
            if (DsQueueLen() == 0) {
                func_00000500();
            }
        } else {
            DsReadyCallback(D_00000610.ready);
            DsStartCallback(D_00000610.start);
            D_00000610.active = 0;
            if (D_00000610.func != 0) {
                D_00000610.func(arg0, arg1, 0);
            }
        }
    }
}
