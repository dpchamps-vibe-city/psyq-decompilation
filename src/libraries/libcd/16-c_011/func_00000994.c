#include "common.h"

static void func_00000994(void *, void *, u32, s32) __asm__("$Lfunc_00000994");

static void func_00000994(void *arg0, void *arg1, u32 arg2, s32 arg3) {
    s32 temp_v0;
    u32 var_v1;
    void *var_a0;
    void *var_a1;

    var_a0 = arg0;
    var_a1 = arg1;
    var_v1 = 0;
    if (arg2 != 0) {
        do {
            temp_v0 = *(s32 *) ((u8 *) var_a1 + 0);
            var_a1 = (void *) ((u8 *) var_a1 + 4);
            var_v1 += 1;
            (*(s32 *) ((u8 *) var_a0 + 0)) = temp_v0;
            var_a0 = (void *) ((u8 *) var_a0 + 4);
        } while (var_v1 < arg2);
    }
}
