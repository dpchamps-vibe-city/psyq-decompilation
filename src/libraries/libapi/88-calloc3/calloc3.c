/* Original TU: library-input/psyq/LIB/LIBAPI.LIB[88] CALLOC3.OBJ
 * sha256: f560701cb5610915f98e3bb80a532fa849b2e33bbf440800af7d637512d7daab
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: calloc3
 */
#include "common.h"
#include "include_asm.h"

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
#include "common.h"

static void func_000000BC(u8 *arg0, s32 arg1) {
    u8 *temp_v1;
    u8 *var_a0;

    var_a0 = arg0;
    temp_v1 = var_a0 + arg1;
    if (var_a0 < temp_v1) {
        do {
            *var_a0 = 0;
            var_a0 += 1;
        } while (var_a0 < temp_v1);
    }
}
