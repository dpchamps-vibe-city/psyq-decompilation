#include "common.h"
#include <sys/types.h>
#include <libpress.h>

static s32 func_000000DC(s16 *src, s16 *dest, s32 size, s32 loop_start,
                        s32 loop, s32 swap, s32 proceed, s16 *work, s32 quality);

long EncSPU2(ENCSPUENV *env) {
    return func_000000DC(env->src, env->dest, (s32)env->size >> 1,
                        (s32)env->loop_start >> 1, (signed char)env->loop,
                        (signed char)env->byte_swap, (signed char)env->proceed,
                        env->work, (signed char)env->quality);
}
