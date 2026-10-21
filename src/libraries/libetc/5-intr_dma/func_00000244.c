#include "common.h"

extern DMAFunc D_0000034C[8];
extern s32 *D_00000348;

DMAFunc func_00000244(s32 index, DMAFunc callback) {
    DMAFunc prev = D_0000034C[index];
    if (callback != prev) {
        if (callback != 0) {
            D_0000034C[index] = callback;
            *(volatile u32 *)D_00000348 =
                (*(volatile u32 *)D_00000348 & 0xFFFFFF) | 0x800000 | ((1 << (index + 16)));
        } else {
            D_0000034C[index] = 0;
            *(volatile u32 *)D_00000348 =
                ((*(volatile u32 *)D_00000348 & 0xFFFFFF) | 0x800000) & ~(1 << (index + 16));
        }
    }
    return prev;
}
