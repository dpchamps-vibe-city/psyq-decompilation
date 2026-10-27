#include "common.h"

extern s32 D_000001A8;
extern s32 B_000001B8[][4];
extern s32 (*B_000001F8[])(s32 *);

void UserFuncExecute(void)
{
    if (D_000001A8 >= 0 && B_000001F8[D_000001A8](B_000001B8[D_000001A8]) != 0)
        D_000001A8--;
}
