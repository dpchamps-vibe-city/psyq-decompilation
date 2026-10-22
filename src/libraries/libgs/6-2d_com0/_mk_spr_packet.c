#include "common.h"
#include <sys/types.h>
#include <libgte.h>

typedef struct {
    u8 code;
    u8 r, g, b;
    u16 tpage;
    u16 cba;
    u8 u, v;
    s16 x, y;
    u16 w, h;
    s16 mx, my;
    u16 flag;
    s32 rotate;
} GsSPKT;

void _mk_normsp(void *arg0, GsSPKT *arg1, MATRIX *arg2, void *arg3);
void _mk_xpndsp(void *arg0, GsSPKT *arg1, MATRIX *arg2, void *arg3);

void _mk_spr_packet(void *arg0, GsSPKT *arg1, MATRIX *arg2, void *arg3) {
    if (arg1->rotate) {
        _mk_xpndsp(arg0, arg1, arg2, arg3);
    } else {
        _mk_normsp(arg0, arg1, arg2, arg3);
    }
}
