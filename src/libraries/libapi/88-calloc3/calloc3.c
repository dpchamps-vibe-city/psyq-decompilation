#include "common.h"

u32 malloc3(s32);                                   /* extern */
static void func_000000BC(u8 *arg0, s32 arg1);

u32 calloc3(s32 arg0, s32 arg1) {
    s32 temp_lo;
    u32 temp_v0;

    temp_lo = arg1 * arg0;
    temp_v0 = malloc3(temp_lo);
    if (temp_v0 == 0) {
        return 0U;
    }
    func_000000BC((u8 *)temp_v0, temp_lo);
    return temp_v0;
}
