#include "common.h"

typedef struct {
    u16 v;
    u16 h;
} GunPos;

extern volatile u32 *D_00000540;
extern u8 *_padGunResultPtr;
extern u8 *_padGunHitCntPtr;
extern s32 D_00000558;
extern s32 D_0000055C;
extern volatile u32 *D_00000564;
extern u16 _padGunPosHbuf[];
extern u16 _padGunPosVbuf[];
extern GunPos *_padGunPosRecv;
extern u16 oldVcount;

u8 _padGetHitCount(void);
void _padClrHitCount(void);

void _padGetGunPos(void)
{
    u8 hits;
    int i;
    u32 vcount;
    volatile u32 *irq;

    *_padGunResultPtr = *(u8 *)&D_00000558;
    D_00000558 = D_0000055C;
    D_0000055C = 0xFF;

    hits = _padGetHitCount();
    *_padGunHitCntPtr = hits;
    if (hits & 0xFF) {
        u8 *cntp;

        cntp = _padGunHitCntPtr;
        for (i = 0; i < *cntp; i++) {
            _padGunPosRecv[i].v = _padGunPosVbuf[i] - oldVcount;
            _padGunPosRecv[i].h = _padGunPosHbuf[i];
        }
        _padClrHitCount();
    }
    vcount = *D_00000540;
    irq = D_00000564;
    irq[0] = 0xFFFFFBFF;
    oldVcount = vcount;
    irq[1] |= 0x400;
}
