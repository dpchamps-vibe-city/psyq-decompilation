#include "common.h"

extern u8 CD_com;
extern u8 CD_mode;
extern void (*CD_cbready)(u8, u8 *);
extern void (*CD_cbsync)(u8, u8 *);
extern s32 CD_status;
extern s32 CD_status1;
extern volatile u8 *D_00001B3C;
extern volatile u8 *D_00001B40;
extern s32 *D_00001B44 __asm__("$LD_00001B44");
extern volatile u8 *D_00001B4C;
extern volatile u8 D_00001B54[];
extern u8 D_00001B58 __asm__("$LD_00001B58");
extern char RO_STR_00001840[] __asm__("$LRO_STR_00001840");
extern char RO_STR_0000184C[] __asm__("$LRO_STR_0000184C");

static void func_00001534(void) __asm__("$Lfunc_00001534");

extern s32 CD_cw(u8 com, u8 *param, u8 *result, s32 mode);
extern s32 CD_sync(s32 mode, u8 *result);
extern int ResetCallback(void);
extern s32 InterruptCallback(s32, void (*)(void));
extern int printf(const char *, ...);
extern int puts(const char *);

s32 CD_init(void) {
    puts(RO_STR_00001840);
    printf(RO_STR_0000184C, &D_00001B58);
    CD_com = 0;
    CD_mode = 0;
    CD_cbready = 0;
    CD_cbsync = 0;
    CD_status1 = 0;
    CD_status = 0;
    ResetCallback();
    InterruptCallback(2, func_00001534);
    *D_00001B3C = 1;
    if (*D_00001B40 & 7) {
        do {
            *D_00001B3C = 1;
            *D_00001B40 = 7;
            *D_00001B4C = 7;
        } while (*D_00001B40 & 7);
    }
    D_00001B54[2] = 0;
    D_00001B54[1] = D_00001B54[2];
    D_00001B54[0] = 2;
    *D_00001B3C = 0;
    *D_00001B40 = 0;
    *D_00001B44 = 0x1325;
    CD_cw(1, 0, 0, 0);
    if (CD_status & 0x10) {
        CD_cw(1, 0, 0, 0);
    }
    if (CD_cw(0xA, 0, 0, 0) != 0) {
        return -1;
    }
    if (CD_cw(0xC, 0, 0, 0) != 0) {
        return -1;
    }
    if (CD_sync(0, 0) != 2) {
        return -1;
    }
    return 0;
}
