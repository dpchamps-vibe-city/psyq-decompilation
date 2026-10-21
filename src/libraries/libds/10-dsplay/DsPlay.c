#include "common.h"
#include <sys/types.h>
#include <libds.h>
#include <stdio.h>

typedef struct {
    s32 field0;
    s32 status;
    s32 result;
    s32 mode;
    s32 track;
    DslLOC toc[100];
    s32 tracks[100];
} DsPlayData;

extern DsPlayData D_000005A8;
extern char RO_STR_00000558[];
extern void func_000001B8(void);
extern void func_000002B4(void);

int DsPlay(int mode, int *tracks, int offset) {
    int i;
    int *p;
    int *q;
    int v;

    if (mode < 3) {
        if (mode <= 0) {
            if (mode == 0) {
                func_000002B4();
            }
        } else {
            if (D_000005A8.status != -1) {
                func_000002B4();
            }
            D_000005A8.result = DsGetToc(D_000005A8.toc);
            if (D_000005A8.result == 0) {
                if (CD_debug > 0) {
                    puts(RO_STR_00000558);
                }
                D_000005A8.status = -1;
            } else {
                i = 0;
                q = D_000005A8.tracks;
                p = tracks;
                for (; i < 99; i++) {
                    v = *p;
                    if (v == 0) {
                        break;
                    }
                    *q++ = v;
                    p++;
                }
                D_000005A8.tracks[i] = 0;
                D_000005A8.mode = (mode != 1);
                D_000005A8.status = offset;
                D_000005A8.track = D_000005A8.tracks[offset];
                func_000001B8();
            }
        }
    }
    return D_000005A8.status;
}
