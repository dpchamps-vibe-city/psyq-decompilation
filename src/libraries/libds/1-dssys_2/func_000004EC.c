#include "common.h"

s32 DS_system_status(s32 arg0);
s32 DS_cw(u8 com, s32 param);
void rescpy(u8 *dst, u8 *src);
void func_00000710_3() __asm__("$Lfunc_00000710");
void func_000000B8(void) __asm__("$Lfunc_000000B8");

extern DsCommand $LB_00001588 __asm__("$LB_00001588");
extern void (*GlobalCallback)(u8, u8 *);
extern s32 $LB_0000167C __asm__("$LB_0000167C");
extern s32 $LB_00001678 __asm__("$LB_00001678");
extern s32 $LB_00001680 __asm__("$LB_00001680");

static void func_000004EC(u8 com, u8 *param) {
    DsCqCommand *cmdq;
    DsCqCommand *cmd;
    DsCqCommand *cmd2;
    DsCq *q;
    s32 off;
    s32 *index;
    s32 *cnt;
    s32 next;
    s32 where;
    s32 status;

    index = &$LB_000015B8.field4;
    cmdq = (DsCqCommand *)((u8 *)index - 0xC4);
    cmd = &cmdq[*index];
    if (cmd->active != 0) {
        $LB_00001588.active = cmd->active;
        $LB_00001588.command = com;
        rescpy($LB_00001588.param, param);
        switch (com & 0xFF) {
        case 2:
            next = *index + 1;
            if (!(next < 8)) {
                where = 0;
            } else {
                where = next;
            }
            if (cmdq[where].active == cmd->active) {
                goto equal2;
            }
            func_00000710_3(cmd->active, 2, param);
            if (cmd->unk10 != 0) {
                ((void (*)(u8, u8 *))cmd->unk10)(2, param);
            }
            func_000000B8();
            break;
        equal2:
            *index = next;
            if (next >= 8) {
                *index = 0;
            }
            break;
        case 5:
            if (cmd->unk14 > 0 || cmd->unk14 == -1) {
                *index = ((DsCq *)cmdq)->index;
                if (cmd->unk14 != -1) {
                    cmd->unk14--;
                }
            } else {
                func_00000710_3(cmd->active, 5, param);
                if (cmd->unk10 != 0) {
                    ((void (*)(u8, u8 *))cmd->unk10)(5, param);
                }
                func_000000B8();
            }
            break;
        }
    }
done:
    if (GlobalCallback != 0) {
        GlobalCallback(com & 0xFF, param);
    }
    status = DS_system_status(0);
    if (status == 1) {
        cnt = &$LB_00001680;
        if (*cnt > 0 && DS_system_status(0) == status) {
            off = $LB_0000167C * 0x18;
            q = (DsCq *)((u8 *)cnt - 0xC8);
            cmd2 = (DsCqCommand *)((u8 *)q + off);
            if (cmd2->active != 0) {
                DS_cw(cmd2->command, cmd2->unkC);
            }
        }
    }
}

