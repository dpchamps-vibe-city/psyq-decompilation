#include "common.h"

extern volatile u32 *D_000001E0;
extern volatile u32 *D_000001E4;

extern u8 * volatile _padGunPosRecv;
extern u8 * volatile _padGunResultPtr;
extern u8 * volatile _padGunHitCntPtr;
extern volatile s32 _padGunExec;
extern s32 _padGunMachType;
extern s16 oldVcount;
extern u32 _padGunSaveTxBuf[2];
extern u32 _padGunSavePadPtr[2];
extern u32 _padGunSaveTxLen[2];

extern void (* volatile _padFuncIntGun)(void);
extern void (* volatile _padFuncSetGunPort)(void);
extern void (* volatile _padFuncGetGunPos)(void);

void _padSetIntH2000(void);
void _padSetGunPort(void);
void _padGetGunPos(void);
void _padClrHitCount(void);
void _padGunInitHook(int, int);
int EnterCriticalSection(void);
void ExitCriticalSection(void);
static int func_000001B8(void);

void PadInitGun(unsigned char *arg0, int arg1) {
    volatile u32 *irq;
    u32 status;
    u32 mask;
    s32 machType;

    irq = (volatile u32 *)0x1F801070;
    EnterCriticalSection();
    _padFuncIntGun = &_padSetIntH2000;
    _padFuncSetGunPort = &_padSetGunPort;
    _padFuncGetGunPos = &_padGetGunPos;
    _padGunPosRecv = arg0 + 2;
    mask = irq[1];
    _padGunResultPtr = arg0;
    irq[1] = mask & ~0x400;
    status = irq[0];
    _padGunExec = 0;
    _padGunHitCntPtr = arg0 + 1;
    irq[0] = status & ~0x400;
    _padClrHitCount();
    _padGunSaveTxBuf[0] = _padGunSaveTxBuf[1] = 0;
    _padGunSavePadPtr[0] = _padGunSavePadPtr[1] = 0;
    oldVcount = 0;
    _padGunSaveTxLen[0] = _padGunSaveTxLen[1] = 0;
    machType = func_000001B8();
    _padGunMachType = machType;
    _padGunInitHook(machType, arg1);
    _padGunExec = 1;
    *D_000001E4 = 0x3E8;
    *D_000001E0 = 0;
    *D_000001E0 = 0x43;
    ExitCriticalSection();
}
