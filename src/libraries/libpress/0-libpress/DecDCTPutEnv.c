#include "common.h"
#include <sys/types.h>
#include <libpress.h>

static void func_00000428(u32 *data, u32 words);
extern u32 D_00000758;
extern s32 D_0000075C;
extern s32 D_0000079C;
extern u32 D_000007DC;

DECDCTENV *DecDCTPutEnv(DECDCTENV *env) {
    DECDCTENV *saved;
    s32 *src;
    s32 *dst;
    s32 *chromaDst;
    s32 value;
    s32 count;
    s32 chromaValue;

    src = (s32 *)env;
    saved = env;
    dst = &D_0000075C;
    count = 15;
    do {
        value = *src++;
        count--;
        *dst++ = value;
    } while (count != -1);
    chromaDst = &D_0000079C;
    src = (s32 *)saved->iq_c;
    count = 15;
    do {
        chromaValue = *src++;
        count--;
        *chromaDst++ = chromaValue;
    } while (count != -1);
    func_00000428(&D_00000758, 32);
    func_00000428(&D_000007DC, 32);
    return saved;
}
