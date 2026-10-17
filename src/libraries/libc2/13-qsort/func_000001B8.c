#include "common.h"

void func_000001B8(void *left, void *right, u32 size) {
    u32 var_a3;
    u8 *temp_a0;
    u8 *temp_v1;
    u8 temp_a1;
    u8 temp_v0;

    var_a3 = 0;
    if (size != 0) {
        do {
            temp_v1 = (u8 *) ((u8 *) left + var_a3);
            temp_a0 = (u8 *) ((u8 *) right + var_a3);
            temp_a1 = *temp_v1;
            temp_v0 = *temp_a0;
            var_a3 += 1;
            *temp_v1 = temp_v0;
            *temp_a0 = temp_a1;
        } while (var_a3 < size);
    }
}
