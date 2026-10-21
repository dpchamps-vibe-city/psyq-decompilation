#include "common.h"

void DS_stop(void);
void DS_CQ_flush(void);
void ER_clear(void);
void DS_restart(void);
s32 DS_cw_system(u8 com, u8 *param);

static void func_000004C4(int arg0) {
    if (D_00000580.active == 1) {
        if (arg0 != 0) {
            DS_stop();
            DS_CQ_flush();
            ER_clear();
            DS_restart();
            DS_cw_system(9, 0);
        } else {
            DsFlush();
        }
        if (D_00000580.mode & 1) {
            DsDataCallback(D_00000580.callback);
        }
    }
    D_00000580.active = 0;
}
