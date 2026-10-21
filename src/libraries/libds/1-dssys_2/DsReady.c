#include "common.h"

typedef unsigned char u_char;

typedef struct {
    s32 active;
    u8 command;
    u8 param[8];
} DsReadyInitCmd;

extern DsReadyInitCmd B_000015A8;
extern DsReadyInitCmd B_00001598;
extern s32 DsReadyModeA __asm__("B_000015A8");
extern s32 DsReadyModeB __asm__("B_00001598");

s32 DS_ready(u8 *arg0);
void rescpy(u8 *dst, u8 *src);

int DsReady(u_char *result) {
    s32 mode;

    DS_ready(0);
    mode = (DsReadyModeA == 1) ? 4 : (DsReadyModeB == 1);
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
