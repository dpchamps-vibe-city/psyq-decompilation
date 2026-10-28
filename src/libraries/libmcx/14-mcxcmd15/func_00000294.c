/* Original member: LIBMCX.LIB[14] MCXCMD15.OBJ */
#include "common.h"
#include "libmcx_transfer.h"
#include "/home/dave/Documents/code/psyq-decomp/build/subagents/1ee81f42-552a-432b-877a-0498ed6fdc7f/a9f39e80-be7d-4ffc-adca-d16415f8e56e/internal-volatile-seq.h"

/* MCXCMD15 .data+0x570: SIO0 register pointer (MMIO 0x1F801040), +4 status.
 * .data+0x574: I_STAT pointer (MMIO 0x1F801070). */
extern vu8 *D_00000570;
extern vu32 *D_00000574;
extern u8 _mcxRxBuf[];
extern u8 _mcxTxBuf[];
extern s32 _mcxPass;

s32 _mcxChkRC2wait(void);
void _mcxSetRC2wait(s32 cmd);
s32 _mcxSioRW(s32 data);

static s32 func_00000294(s32 value) {
    s32 rest;
    s32 rx;
    u8 c;
    u8 tx;

    if (_mcxPass == 1) {
        if (_mcxRxLen == 4) {
            _mcxDataLen = value & 0xFF;
        } else if (_mcxRxLen == 0xD) {
            if (_mcxSum != 0) {
                _mcxPass = 0;
            }
        }
        if (_mcxRxLen < 4) {
            return 0;
        }
        if (_mcxRxLen == _mcxDataLen + 4) {
            do {
            } while (!(*(vu16 *)(D_00000570 + 4) & 2));
            _mcxFlag = 1;
            _mcxPtrBuff = (u8 *)_mcxPtrCmdBuf0;
            c = *D_00000570;
            _mcxRestSize = _mcxRxBuf[_mcxRxLen++] = c;
            _mcxCmdSeq++;
            _mcxSetRC2wait(0x1AE);
            while (!(*D_00000574 & 0x80)) {
                if (_mcxChkRC2wait() != 0) {
                    return -1;
                }
            }
            tx = _mcxFuncGetTx();
            _mcxTxBuf[_mcxTxLen++] = tx;
            if (_mcxSioRW(tx & 0xFF) < 0) {
                return -2;
            }
        } else if (_mcxRxLen == _mcxDataLen + 5) {
            if (_mcxRestSize >= 3) {
                _mcxStartFastDsr(1, _mcxPtrBuff + 1, _mcxRestSize - 2, &_mcxSum);
                rx = _mcxRxLen - 2;
                rest = _mcxRestSize;
                _mcxRestSize = 2;
                _mcxRxLen = rx + rest;
                _mcxTxLen -= 2;
                _mcxTxLen += rest;
            }
        }
        return 0;
    }
    if (_mcxRxLen == 3) {
        _mcxRestSize = value & 0xFF;
        return 0;
    }
    if (_mcxRxLen < 3) {
        return 0;
    }
    if (_mcxRxLen < 6) {
        if (_mcxPass == 4 && (value & 0xFF)) {
            _mcxSum = 1;
            _mcxRestSize = 1;
            _mcxPass = 2;
        } else {
            _mcxSum = 0;
        }
    }
    return 0;
}
