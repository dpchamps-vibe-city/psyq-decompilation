/* Original member: LIBMCX.LIB[9] MCXCMD10.OBJ */
#include "common.h"
#include "libmcx_transfer.h"

/* MCXCMD10 .data+0x360: SIO0 register pointer (MMIO 0x1F801040), +4 status.
 * .data+0x364: I_STAT pointer (MMIO 0x1F801070). Storage remains in _data.c;
 * these declarations supply its source type. */
extern vu8 *D_00000360;
extern vu32 *D_00000364;
extern u8 _mcxRxBuf[];
extern u8 _mcxTxBuf[];
extern s32 _mcxFlag;
extern volatile s32 _mcxCmdSeq;
extern u8 *_mcxPtrCmdBuf0;
extern s32 (*_mcxFuncGetTx)(void);

s32 _mcxChkRC2wait(void);
void _mcxSetRC2wait(s32 cmd);
s32 _mcxSioRW(s32 data);

s32 _mcxRxReadDev(s32 value) {
    s32 rest;
    s32 rx;
    u8 c;
    u8 data = value;

    if (_mcxRxLen == 4) {
        _mcxDataLen = data & 0xFF;
    }
    if (_mcxRxLen < 4) {
        return 0;
    }
    if (_mcxRxLen == _mcxDataLen + 4) {
        while (!(*(vu16 *)(D_00000360 + 4) & 2)) {
        }
        _mcxFlag = 1;
        _mcxPtrBuff = _mcxPtrCmdBuf0;
        c = *D_00000360;
        _mcxRestSize = (_mcxRxBuf[_mcxRxLen++] = c) & 0xFF;
        if (_mcxRestSize != 0) {
            _mcxCmdSeq++;
            _mcxSetRC2wait(0x1AE);
            while (!(*D_00000364 & 0x80)) {
                if (_mcxChkRC2wait() != 0) {
                    return -1;
                }
            }
            c = _mcxFuncGetTx();
            _mcxTxBuf[_mcxTxLen++] = c;
            if (_mcxSioRW(c & 0xFF) < 0) {
                return -2;
            }
        }
    } else if (_mcxRxLen == _mcxDataLen + 5) {
        if (_mcxRestSize >= 3) {
            _mcxStartFastDsr(0, _mcxPtrBuff, _mcxRestSize - 2, &_mcxSum);
            rx = _mcxRxLen - 2;
            rest = _mcxRestSize;
            _mcxRestSize = 2;
            _mcxRxLen = rx + rest;
            _mcxTxLen -= 2;
            _mcxTxLen += rest;
        }
    } else if (_mcxRxLen > _mcxDataLen + 5) {
        _mcxPtrBuff[_mcxRxLen - _mcxDataLen - 6] = value;
    }
    return 0;
}
