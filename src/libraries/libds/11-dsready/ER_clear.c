#include "common.h"

void ER_clear(void) {
    if (D_00000610.active == 1) {
        DsReadyCallback(D_00000610.ready);
        DsStartCallback(D_00000610.start);
    }
    D_00000610.active = 0;
}
