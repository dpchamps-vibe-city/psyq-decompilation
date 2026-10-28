INCLUDE_ASM("build/libraries/nonmatchings/libpad_8", _padSetGunPort);


/* PARKED by /auto_decompilation_loop on 2026-10-28T19:48:56.446Z.
 * Reason: escalation-exhausted.
 * Escalation reached: gpt-6.1-sol.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libpad_8::_padSetGunPort.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include "libpad-internal.h"

extern PadInfo2 *_padInfoDir;
extern u8 _padGunEnalePort;
extern u8 D_00000568;
extern u8 D_00000569;
extern u8 D_0000056A;
extern s32 D_00000558;
extern s32 D_0000055C;
extern s32 B_00000570;
extern u8 B_00000578[8];

PadInfo2 *_padGunSavePadPtr[2];
u8 *_padGunSaveTxBuf[2];
s32 _padGunSaveTxLen[2];

void _padSetGunPort(void) {
    PadInfo2 *pad;
    u32 bit;
    u32 enable;
    u32 mask;
    int mtap;
    u8 *row;
    u8 *cntp;
    u8 *cmdp;
    int i;
    int j;

    if (_padGunSavePadPtr[0] != 0) {
        _padGunSavePadPtr[0]->actTable = _padGunSaveTxBuf[0];
        _padGunSavePadPtr[0]->actSize = _padGunSaveTxLen[0];
        _padGunSavePadPtr[0] = 0;
        _padGunSaveTxBuf[0] = 0;
    }
    if (_padGunSavePadPtr[1] != 0) {
        _padGunSavePadPtr[1]->actTable = _padGunSaveTxBuf[1];
        _padGunSavePadPtr[1]->actSize = _padGunSaveTxLen[1];
        _padGunSavePadPtr[1] = 0;
        _padGunSaveTxBuf[1] = 0;
    }

    mask = 0;
    for (i = 0; i < 2; i++) {
        if (_padInfoDir[i].mtapType == 8) {
            pad = _padInfoDir[i].child;
            for (j = 0; j < 4; j++) {
                if (pad->mtapType == 3) {
                    mask |= 1 << (j + i * 4);
                }
                pad++;
            }
        } else if (_padInfoDir[i].mtapType == 3) {
            if (i != 0) {
                mask = (mask & 0xFF) | 0x10;
            } else {
                mask = (mask & 0xFF) | 0x01;
            }
        }
    }

    enable = mask & _padGunEnalePort;
    if (enable != (D_00000568 & D_00000569)) {
        B_00000570 = 0;
        bit = 1;
        for (i = 0; i < 2; i++) {
            row = &B_00000578[i * 4];
            for (j = 0; j < 4; j++) {
                if (enable & bit) {
                    u8 cnt = B_00000570;
                    if (_padInfoDir[i].mtapType == 8) {
                        cnt++;
                    }
                    row[j] = cnt;
                    B_00000570++;
                }
                bit <<= 1;
            }
        }
        D_00000568 = mask;
        D_00000569 = _padGunEnalePort;
    }

    mtap = 8;
    cntp = (u8 *)&B_00000570;
    bit = 1;
    row = B_00000578;
    cmdp = &D_0000056A;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            if (enable & bit) {
                if (row[j] == 0) {
                    if (_padInfoDir[i].mtapType == mtap) {
                        pad = (i ? &_padInfoDir[1] : &_padInfoDir[0])->child + j;
                        _padGunSavePadPtr[i] = pad;
                        D_0000055C = i * 16 + j;
                    } else {
                        pad = i ? &_padInfoDir[1] : &_padInfoDir[0];
                        _padGunSavePadPtr[i] = pad;
                        D_00000558 = i * 16 + j;
                    }
                    row[j] = *cntp - 1;
                    _padGunSaveTxBuf[i] = pad->actTable;
                    _padGunSaveTxLen[i] = pad->actSize;
                    pad->actTable = cmdp;
                    pad->actSize = 1;
                } else {
                    row[j]--;
                }
            }
            bit <<= 1;
        }
        row += 4;
    }
}
#endif
