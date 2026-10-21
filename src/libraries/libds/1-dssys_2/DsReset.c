#include "common.h"

extern u8 B_0000158D[];
extern u8 B_0000159D[];
extern u8 B_000015AD[];
extern u8 B_00001688[];
extern s32 B_00001708;
extern s32 B_00001678;
extern s32 B_0000167C;
extern s32 B_00001680;
extern void (*GlobalCallback)(u8, u8 *);

void DS_stop(void);
void ER_clear(void);
int DsReadySystemMode(int);
void DS_restart(void);

int DsReset(void) {
    s32 i;
    s32 j;
    s32 k;
    s32 off;
    u8 *gp;
    DsInitCmd *p;
    void (*flush)(DsCommand *);

    DS_stop();
    gp = (u8 *)&GlobalCallback;
    *(s32 *)(gp + 0) = 0;
    *(s32 *)(gp + 4) = 0;
    *(s32 *)(gp + 8) = 0;

    p = B_00001588;
    p[2].active = 0;
    p[1].active = 0;
    p[0].active = 0;
    p[2].command = 0;
    p[1].command = 0;
    p[0].command = 0;
    for (i = 0; i < 8; i++) {
        B_0000158D[i] = 0;
        B_0000159D[i] = 0;
        B_000015AD[i] = 0;
    }
    for (j = 0; j < 8; j++) {
        flush = func_00000088;
        flush(&B_000015B8.command[j]);
    }
    B_0000167C = 0;
    B_00001678 = 0;
    B_00001680 = 0;
    for (k = 7, off = 0x70; k >= 0; k--, off -= 0x10) {
        *(s32 *)(B_00001688 + off) = 0;
    }
    B_00001708 = 0;
    ER_clear();
    DsReadySystemMode(0);
    DS_restart();
    return 1;
}
