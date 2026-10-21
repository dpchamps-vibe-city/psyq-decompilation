#include "common.h"

int VSync(int mode);
int DsReady(u_char *result);
static void func_000004C4(int arg0);

int DsReadSync(u_char *result) {
    int ret = -1;

    if (VSync(-1) > D_00000580.vsync + 0x4B0) {
        func_000004C4(1);
    } else {
        ret = D_00000580.sectors;
    }
    DsReady(result);
    return ret;
}
