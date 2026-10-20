#include "common.h"

typedef void (*DsInitCB)(u8, u8 *);

typedef struct {
    s32 active;
    u8 command;
    u8 param[8];
} DsInitCmd;

extern DsInitCmd B_00001588[] __asm__("$LB_00001588");
extern u8 B_0000158D[] __asm__("$LB_0000158D");
extern u8 B_0000159D[] __asm__("$LB_0000159D");
extern u8 B_000015AD[] __asm__("$LB_000015AD");
extern u8 B_00001688B[] __asm__("$LB_00001688");
extern s32 B_00001708 __asm__("$LB_00001708");

s32 DS_system_active(void);
void DS_init(void);
void DS_sync_callback(DsInitCB);
void DS_ready_callback(DsInitCB);
void DS_start_callback(DsInitCB);
void DS_vsync_callback(DsInitCB);
void ER_clear(void);
int DsReadySystemMode(int);
int DsQueueLen(void);
extern void DsInitFlush(DsCommand *) __asm__("$Lfunc_00000088");
extern void DsInitReadyCb(u8, u8 *) __asm__("$Lfunc_00000088+4836");
extern void DsInitStartCb(u8, u8 *) __asm__("$Lfunc_00000088+5048");
extern void DsInitVsyncCb(u8, u8 *) __asm__("$Lfunc_00000088+4672");

int DsInit(void) {
    s32 i;
    s32 j;
    s32 k;
    s32 off;
    u8 *gp;
    DsInitCmd *p;

    if (DS_system_active() != 0) {
        return 0;
    }
    {
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
            DsInitFlush((DsCommand *)&$LB_000015B8.command[j]);
        }
        $LB_0000167C = 0;
        $LB_00001678 = 0;
        $LB_00001680 = 0;
        for (k = 7, off = 0x70; k >= 0; k--, off -= 0x10) {
            *(s32 *)(B_00001688B + off) = 0;
        }
        B_00001708 = 0;
        DS_init();
        DS_sync_callback(func_000004EC);
        DS_ready_callback((DsInitCB)DsInitReadyCb);
        DS_start_callback((DsInitCB)DsInitStartCb);
        DS_vsync_callback((DsInitCB)DsInitVsyncCb);
        ER_clear();
        DsReadySystemMode(0);
    }
    return 1;
}
