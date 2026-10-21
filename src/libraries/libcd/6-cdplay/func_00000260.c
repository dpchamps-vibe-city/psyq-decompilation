#include "common.h"

static void func_00000260(u_char com, u_char *result)
{
    s32 i;
    s32 n;

    if (com == 1) {
        for (i = 0; i < 8; i++) {
            B_000009B0[i] = result[i];
        }
        n = (B_000009B0[1] >> 4) * 10 + (B_000009B0[1] & 0xF);
        if (D_00000808[0] < n) {
            com = 4;
        }
    }
    if (com == 4) {
        CdReadyCallback(0);
        if (CD_debug >= 2) {
            printf(RO_STR_00000600, D_000007FC, VSync(-1));
        }
        D_000007FC++;
        D_00000808[0] = D_0000066C[D_000007FC];
        func_000003EC();
    } else if (com == 5) {
        if (!(result[0] & 1)) {
            D_00000800 = 1;
            if (CD_debug >= 2) {
                printf(RO_STR_0000062C, CdIntstr(5), result[0], result[1]);
            }
            if (!(result[0] & 0x11)) {
                func_000003EC();
            }
        }
    }
}
