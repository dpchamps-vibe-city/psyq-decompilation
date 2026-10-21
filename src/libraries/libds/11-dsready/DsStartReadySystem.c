#include "common.h"

typedef unsigned char u_char;
typedef unsigned long u_long;

typedef void (*DslCB)(u_char, u_char *);
typedef void (*DslRCB)(u_char, u_char *, u_long *);

typedef struct {
    s32 pos;        /* 0x610 */
    s32 unk4;       /* 0x614 */
    DslRCB func;    /* 0x618 */
    s32 unkC;       /* 0x61C */
    s32 count;      /* 0x620 */
    DslCB ready;    /* 0x624 */
    DslRCB start;   /* 0x628 */
    s32 mode;       /* 0x62C */
    s32 active;     /* 0x630 */
} DsReadyState;

extern DsReadyState D_00000610;

DslCB DsReadyCallback(DslCB func);
DslRCB DsStartCallback(DslRCB func);

static void func_0000016C(u_char, u_char *);
static void func_00000448(u_char, u_char *, u_long *);

int DsStartReadySystem(DslRCB func, int count) {
    if (D_00000610.active == 1) {
        return 0;
    }
    D_00000610.pos = -1;
    D_00000610.unk4 = 0;
    D_00000610.unkC = 0;
    D_00000610.func = func;
    D_00000610.count = count;
    D_00000610.ready = DsReadyCallback(func_0000016C);
    D_00000610.start = DsStartCallback(func_00000448);
    D_00000610.active = 1;
    return 1;
}
