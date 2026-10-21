#include "common.h"

extern DslCB D_000005A4;

DslCB DsReadCallback(DslCB func) {
    DslCB temp_v0;

    temp_v0 = D_000005A4;
    D_000005A4 = func;
    return temp_v0;
}
