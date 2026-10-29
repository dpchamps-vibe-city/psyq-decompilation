#include "common.h"
#include <sys/types.h>
#include <libpress.h>

long EncSPU(ENCSPUENV *env) {
    return func_000001F4((u16 *)env->src, (u16 *)env->dest,
                        (s32)env->size >> 1, (s32)env->loop_start >> 1,
                        (signed char)env->loop, (signed char)env->byte_swap,
                        (signed char)env->proceed, env->work);
}
