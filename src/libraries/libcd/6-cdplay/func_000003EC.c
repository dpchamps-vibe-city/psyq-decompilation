#include "common.h"

extern s32 CD_debug;
extern char RO_STR_00000648[];

static void func_000003EC(void) {
    s32 temp_a1;
    s32 var_v1;
    u_char *var_v0;

    D_00000800 = 0;
    if (D_0000066C[D_000007FC] == 0) {
        if (D_00000804 != 0) {
            D_000007FC = 0;
            D_00000808[0] = D_0000066C[0];
        } else {
            D_000007FC = -1;
            func_00000564();
        }
    }
    var_v1 = 7;
    if (D_000007FC >= 0) {
        var_v0 = (u_char *)B_00000818 + 415;
        do {
            *var_v0 = 0;
            var_v1 -= 1;
            var_v0 -= 1;
        } while (var_v1 >= 0);
        D_00000668 += 1;
        temp_a1 = D_0000066C[D_000007FC];
        if (B_000009A8 < temp_a1) {
            if (CD_debug >= 2) {
                printf(RO_STR_00000648, temp_a1);
            }
            D_0000066C[D_000007FC] = B_000009A8;
        }
        CdReadyCallback(func_00000260);
        CdControl(3U, &B_00000818[D_0000066C[D_000007FC]].minute, 0);
    }
}
