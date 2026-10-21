#include "common.h"

s32 DS_system_status(s32 arg0);
s32 DS_cw(u8 com, s32 param);

#define func_0000047C $Lfunc_0000047C

static s32 func_0000047C(void);

static s32 func_0000047C(void) {
    s32 ret;
    DsCqCommand *cmd;
    s32 (*self)(void);

    self = func_0000047C;
    (void) self;

    if (DS_system_status(0) != 1) {
        ret = 0;
    } else {
        cmd = &B_000015B8.command[B_000015B8.field4];
        if (cmd->active == 0) {
            ret = 0;
        } else {
            ret = DS_cw(cmd->command, cmd->unkC) != 0;
        }
    }
    return ret;
}

#undef func_0000047C

#define PUBLISHED_ENTRY() static s32 func_0000047C(void) { return $Lfunc_0000047C(); }
PUBLISHED_ENTRY();
