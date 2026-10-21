#include "common.h"

extern DsCq B_000015B8;

void DS_CQ_flush(void) {
    DsCommand *p;
    s32 *q;
    s32 i;
    s32 j;
    u8 *r;

    q = &B_000015B8.count;
    q[0] = 0;
    q[-1] = 0;
    q[-2] = 0;
    for (i = 0; i < 8; i++) {
        p = &B_000015B8.command[i];
        j = 3;
        r = (u8 *) p + 3;
        p->active = 0;
        *((u8 *) p + 4) = 0;
        do {
            r[5] = 0;
            j--;
            r--;
        } while (j >= 0);
        p->unkC = 0;
        p->unk10 = 0;
        p->unk14 = 0;
    }
}
