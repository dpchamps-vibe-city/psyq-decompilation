#include "common.h"
#include <sys/types.h>
#include <libds.h>
#include <stdio.h>

extern DsPlayData D_000005A8;
extern s32 D_000005AC;
extern char RO_STR_00000558[];
extern u_char B_000008E8[];

s32 ER_active(void);

static void func_000002F4(u_char, u_char *);

void func_00000344(u_char mode, u_char *arg1, u_long *arg2) {
    DslLOC pos;
    s32 i;
    u_char b;

    if (mode == 1) {
        for (i = 0; i < 8; i++) {
            B_000008E8[i] = arg1[i];
        }
        b = B_000008E8[1];
        if (D_000005A8.track < ((b >> 4) * 10 + (b & 0xF))) {
            mode = 4;
        }
    }
    if (mode == 4) {
        DsEndReadySystem();
        D_000005A8.status++;
        D_000005A8.track = D_000005A8.tracks[D_000005A8.status];
        if (D_000005A8.track == 0) {
            if (D_000005A8.mode != 0) {
                D_000005A8.status = 0;
                D_000005A8.track = D_000005A8.tracks[0];
            } else {
                D_000005A8.status = -1;
                DsEndReadySystem();
                DsCommand(9, NULL, NULL, -1);
                D_000005A8.status = -1;
            }
        }
        if (D_000005A8.status != -1) {
            if (D_000005AC < 0) {
                if (CD_debug > 0) {
                    printf(RO_STR_00000558 + 28, D_000005AC);
                }
            } else {
                if (ER_active() == 0) {
                    pos = D_000005A8.toc[D_000005A8.tracks[D_000005A8.status]];
                    *((s32 *)&D_000005AC - 1) = DsPacket(5, &pos, 3, func_000002F4, -1);
                    if (*((s32 *)&D_000005AC - 1) == 0) {
                        if (CD_debug > 0) {
                            puts(RO_STR_00000558 + 52);
                        }
                        D_000005A8.status = -1;
                    }
                } else {
                    D_000005A8.status = -1;
                }
            }
        }
    }
}
