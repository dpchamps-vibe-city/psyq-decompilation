#include "common.h"
#include <libapi.h>
#include <sys/types.h>
#include <libcd.h>
#include <libetc.h>
#include <stdio.h>

static void func_000001F0(s32, s32);
extern volatile s32 *D_000002A0;
extern volatile s32 *D_000002A4;
extern volatile s32 D_000002AC;
extern volatile s32 Hcount;
extern volatile s32 Vcount;

int VSync(int mode) {
    volatile s32 sp10;
    s32 temp_s0;
    s32 temp_s1;
    s32 var_a1;
    s32 var_v0;
    s32 t;

    temp_s0 = *D_000002A0;

    do {
        sp10 = *D_000002A4;
    } while (sp10 != *D_000002A4);
    temp_s1 = (sp10 - Hcount) & 0xFFFF;
    if (mode < 0) {
        return Vcount;
    }
    if (mode != 1) {
        if (mode > 0) {
            t = D_000002AC - 1;
            var_v0 = t + mode;
        } else {
            var_v0 = D_000002AC;
        }
        var_a1 = 0;
        if (mode > 0) {
            var_a1 = mode - 1;
        }
        func_000001F0(var_v0, var_a1);
        temp_s0 = *D_000002A0;
        func_000001F0(Vcount + 1, 1);
        if ((temp_s0 & 0x400000) && ((temp_s0 ^ *D_000002A0) >= 0)) {
            do {

            } while (!((temp_s0 ^ *D_000002A0) & 0x80000000));
        }
        D_000002AC = Vcount;
        do {
            Hcount = *D_000002A4;
        } while (Hcount != *D_000002A4);
    }
    return temp_s1;
}
