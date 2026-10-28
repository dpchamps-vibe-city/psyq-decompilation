#include "common.h"
#include "libmcx_resi.h"

int _mcxStepSio(void) {
    int tx;
    int received;

    if (_mcxCmdSeq == 1) {
        _mcxStat = 4;
        _mcxInitSioMode(_mcxPort >> 4);
        _mcxSioRW(~((_mcxPort & 0xF) + 0x81));
        _mcxTxBuf[0] = (((unsigned char *)&_mcxPort)[0] & 0xF) - 0x7F;
        _mcxTxLen++;
        return 0;
    }
    _mcxRestSize--;
    tx = _mcxFuncGetTx() & 0xFF;
    _mcxTxBuf[_mcxTxLen++] = tx;
    received = _mcxSioRW(tx);
    if (received < 0) {
        return received - 1000;
    }
    _mcxRxBuf[_mcxRxLen++] = received;
    received = _mcxFuncApplyRx(received & 0xFF);
    if (received != 0) {
        return received - 2000;
    }
    if (_mcxRestSize == 0) {
        return 1;
    }
    if (_mcxRestSize == 1) {
        if (((_mcxFuncNo != 14) && (_mcxFuncNo != 15)) ||
            (_mcxRxLen != _mcxDataLen + 4)) {
            while (!(*(volatile unsigned short *)(D_00000574 + 4) & 2)) {
            }
        }
        _mcxCmdSeq++;
        _mcxRestSize--;
        received = D_00000574[0];
        _mcxRxBuf[_mcxRxLen++] = received;
        received = _mcxFuncApplyRx(received);
        if (received != 0) {
            return received - 3000;
        }
        return 1;
    }
    return 0;
}
