#include "common.h"

typedef struct {
    u16 hi;
    u16 pad;
    s16 lo;
} Conf474;

typedef struct {
    u32 f0;
    u32 f4;
    u32 f8;
} ConfOut474;

static void *func_0000036C(u32 arg0, u32 arg1, u32 arg2) {
    Conf474 *r = *(Conf474 **)0x474;
    ConfOut474 *w = (ConfOut474 *)((r->hi << 16) + (r->lo - 8));

    w->f0 = arg1;
    w->f4 = arg0;
    w->f8 = arg2;
    return w;
}
