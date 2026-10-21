#include "common.h"

typedef unsigned char u_char;

typedef struct {
    s32 active;
    u8 command;
    u8 param[8];
} DsReadyInitCmd;

extern DsReadyInitCmd DsReadyB15A8 __asm__("$LB_000015A8");
extern DsReadyInitCmd DsReadyB1598 __asm__("$LB_00001598");
extern s32 DsReadyModeA __asm__("$LB_000015A8");
extern s32 DsReadyModeB __asm__("$LB_00001598");

s32 DS_ready(u8 *arg0);
void rescpy(u8 *dst, u8 *src);

int DsReady(u_char *result) {
    s32 mode;

    DS_ready(0);
    mode = (DsReadyModeA == 1) ? 4 : (DsReadyModeB == 1);
    if (mode == 4) {
        DsReadyB15A8.active = 0;
        rescpy(result, DsReadyB15A8.param);
        return DsReadyB15A8.command;
    } else if (mode == 1) {
        DsReadyB1598.active = 0;
        rescpy(result, DsReadyB1598.param);
        return DsReadyB1598.command;
    }
    return 0;
}
