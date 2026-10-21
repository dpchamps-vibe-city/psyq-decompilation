#include "common.h"

typedef void (*DslRCB)(u_char, u_char *, u_long *);

int DsStartReadySystem(DslRCB func, int count);

static void func_000001D4(u_char, u_char *, u_long *);

static void func_000001A0(u_char arg0, u_char *arg1) {
    if (arg0 == 2) {
        DsStartReadySystem(func_000001D4, -1);
    }
}
