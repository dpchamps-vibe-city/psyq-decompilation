#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

static void func_00000A40(u32 *arg0, u32 *arg1, u32 *arg2) {
    (*(s16 *) ((u8 *) arg0 + 0)) = (s16) ((s32) ((*(s16 *) ((u8 *) arg1 + 0)) + (*(s16 *) ((u8 *) arg2 + 0))) / 2);
    (*(s16 *) ((u8 *) arg0 + 2)) = (s16) ((s32) ((*(s16 *) ((u8 *) arg1 + 2)) + (*(s16 *) ((u8 *) arg2 + 2))) / 2);
    (*(s16 *) ((u8 *) arg0 + 4)) = (s16) ((s32) ((*(s16 *) ((u8 *) arg1 + 4)) + (*(s16 *) ((u8 *) arg2 + 4))) / 2);
    (*(s8 *) ((u8 *) arg0 + 6)) = (s8) ((s32) ((*(u8 *) ((u8 *) arg1 + 6)) + (*(u8 *) ((u8 *) arg2 + 6))) >> 1);
    (*(s8 *) ((u8 *) arg0 + 7)) = (s8) ((s32) ((*(u8 *) ((u8 *) arg1 + 7)) + (*(u8 *) ((u8 *) arg2 + 7))) >> 1);
}
