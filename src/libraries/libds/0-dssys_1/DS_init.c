#include "common.h"

typedef void (*DslCB)(u8, u8 *);

extern void CD_init(void);
extern void CD_initvol(void);
extern s32 DsReadMode(s32);
extern void VSyncCallbacks(s32, void (*)(u8, u8 *, s32 *, s32 *));
extern void DS_reset_members(void);

static void func_00000590(u8, u8 *, s32 *, s32 *);
static void func_000008E8(u8, u8 *);
static void func_00000F50(u8, u8 *);

extern DslCB CD_cbsync;
extern DslCB CD_cbready;
extern s32 DS_active;
extern s32 DS_shell;
extern volatile DslCB B_000013A0;
extern volatile DslCB B_0000139C;
extern volatile DslCB B_00001398;
extern volatile s32 LD_00001240 __asm__("D_00001240");

void DS_init(void) {
    CD_init();
    CD_initvol();
    B_000013A0 = 0;
    B_0000139C = B_000013A0;
    B_00001398 = 0;
    DS_reset_members();
    DS_shell = 0;
    DsReadMode(0);
    CD_cbsync = func_000008E8;
    CD_cbready = func_00000F50;
    VSyncCallbacks(0, func_00000590);
    DS_active = 1;
    LD_00001240 = 1;
}
