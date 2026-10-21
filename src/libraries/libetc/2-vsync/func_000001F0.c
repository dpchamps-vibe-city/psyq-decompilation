#include "common.h"
#include <libapi.h>
#include <sys/types.h>
#include <libetc.h>
#include <stdio.h>

void ChangeClearRCnt(long, long);
extern volatile s32 Vcount;
extern char RO_STR_00000288[];

static void func_000001F0(s32 vcount, s32 timeout) {
    volatile s32 count;

    count = timeout << 15;
    while (Vcount < vcount) {
        count--;
        if (count == -1) {
            puts(RO_STR_00000288);
            ChangeClearPAD(0);
            ChangeClearRCnt(3, 0);
            return;
        }
    }
}
