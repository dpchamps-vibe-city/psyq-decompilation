#include "common.h"

typedef struct {
    s32 id;
    void (*cb)(u8, u8 *);
} DsCb;

extern s32 B_00001678;
extern s32 B_0000167C;
extern s32 B_00001680;

static void func_00000710(s32, u8, u8 *, s32);

static void func_0000028C(u8 arg0, u8 *arg1, s32 arg2, s32 arg3);

static void func_0000028C(u8 arg0, u8 *arg1, s32 arg2, s32 arg3) {
    DsCb callbacks[8];
    s32 i;
    s32 j;
    s32 id;
    s32 slot;
    s32 last;
    s32 previd;
    s32 cb;

    for (i = 0; i < 8; i++) {
        callbacks[i].id = 0;
        callbacks[i].cb = 0;
    }
    slot = B_000015B8.index;
    previd = 0;
    last = -1;
    for (i = 0; i < B_000015B8.count; i++) {
        id = B_000015B8.command[slot].active;
        if (id != previd) {
            func_00000710(id, arg0, arg1, arg3);
            previd = id;
        }
        cb = B_000015B8.command[slot].unk10;
        arg3 = -1;
        if (cb != 0) {
            if (last == arg3) {
                last = 0;
                callbacks[last].id = id;
            } else if (callbacks[last].id != id) {
                last++;
                callbacks[last].id = id;
            } else {
                goto next;
            }
            callbacks[last].cb = (void (*)(u8, u8 *))cb;
        }
    next:
        slot++;
        if (slot >= 8) {
            slot = 0;
        }
    }
    B_00001680 = 0;
    B_0000167C = 0;
    B_00001678 = 0;
    for (j = 0; j < 8; j++) {
        DsCqCommand *cmd = &B_000015B8.command[j];
        s32 k;
        u8 *r;

        k = 3;
        r = (u8 *) cmd + 3;
        cmd->active = 0;
        *((u8 *) cmd + 4) = 0;
        do {
            r[5] = 0;
            k--;
            r--;
        } while (k >= 0);
        cmd->unkC = 0;
        cmd->unk10 = 0;
        cmd->unk14 = 0;
    }
    for (i = 0; i <= last; i++) {
        callbacks[i].cb(arg0, arg1);
    }
}
