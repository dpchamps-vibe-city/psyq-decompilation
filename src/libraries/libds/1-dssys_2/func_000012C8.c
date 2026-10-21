#include "common.h"

s32 DS_system_status(s32 arg0);
s32 DS_cw(u8 com, s32 param);

extern s32 B_0000167C;
extern s32 B_00001680;

void func_000012C8(u8 arg0, u8 *arg1) {
    DsCommand *cmd2;
    DsCq *q;
    s32 *cnt;
    s32 off;
    s32 status;

    status = DS_system_status(0);
    if (status == 1) {
        cnt = &B_00001680;
        if (*cnt > 0 && DS_system_status(0) == status) {
            off = B_0000167C * 0x18;
            q = (DsCq *)((u8 *)cnt - 0xC8);
            cmd2 = (DsCommand *)((u8 *)q + off);
            if (cmd2->active != 0) {
                DS_cw(cmd2->command, cmd2->unkC);
            }
        }
    }
}
