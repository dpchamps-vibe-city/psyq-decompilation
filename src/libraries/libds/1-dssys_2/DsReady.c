#include "common.h"

typedef unsigned char u_char;

extern DsInitCmd B_000015A8;
extern DsInitCmd B_00001598;

s32 DS_ready(u8 *arg0);
void rescpy(u8 *dst, u8 *src);

int DsReady(u_char *result) {
    s32 mode;

    DS_ready(0);
    mode = (B_000015A8.active == 1) ? 4 : (B_00001598.active == 1);
    if (mode == 4) {
        B_000015A8.active = 0;
        rescpy(result, B_000015A8.param);
        return B_000015A8.command;
    } else if (mode == 1) {
        B_00001598.active = 0;
        rescpy(result, B_00001598.param);
        return B_00001598.command;
    }
    return 0;
}
