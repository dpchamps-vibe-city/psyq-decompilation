#include "common.h"
#include <stdio.h>

extern s32 D_000001A8;
extern s32 B_000001B8[][4];
extern s32 (*B_000001F8[])(s32 *);
extern char RO_STR_00000188[];

extern void UserFuncOpen(s32 (*callback)(s32 *));

void UserFuncOpen(s32 (*callback)(s32 *))
{
    s32 n;
    s32 i;

    n = D_000001A8 + 1;
    if (n >= 4) {
        printf(RO_STR_00000188);
        return;
    }
    D_000001A8 = n;
    B_000001F8[n] = callback;
    for (i = 3; i >= 0; i--)
        B_000001B8[n][i] = 0;
}
