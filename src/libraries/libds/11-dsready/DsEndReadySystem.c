#include "common.h"

int DsCommand(u_char com, u_char *param, DslCB cbsync, int count);

void DsEndReadySystem(void) {
    if (D_00000610.active == 1) {
        DsReadyCallback(D_00000610.ready);
        DsStartCallback(D_00000610.start);
        DsCommand(9, 0, 0, -1);
    }
    D_00000610.active = 0;
}
