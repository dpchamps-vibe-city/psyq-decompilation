#include "common.h"
#include <sys/types.h>
#include <libcd.h>

static void func_000000EC(void);
extern void data_ready_callback(void);
extern s32 StMode;

int CdRead2(long mode) {
    s8 sp10;

    sp10 = mode;
    CdControl(CdlSetmode, (u_char *)&sp10, 0);
    if (mode & 0x100) {
        if (mode & 0x20) {
            StMode = 0;
        } else {
            StMode = 1;
        }
        CdDataCallback(data_ready_callback);
        CdReadyCallback((CdlCB)func_000000EC);
    }
    CdControl(CdlReadS, 0, 0);
}

