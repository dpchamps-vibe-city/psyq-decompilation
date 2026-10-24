#include "common.h"
#include <stdio.h>

extern s32 D_000024DC;
extern char RO_STR_00001ED8[];

s32 dmyGsPrstTF3LFG(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_000024DC == 0) {
        printf(RO_STR_00001ED8 + 212);
        D_000024DC = 1;
    }
    return arg3;
}
