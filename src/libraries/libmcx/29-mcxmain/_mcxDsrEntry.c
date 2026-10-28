#include "common.h"
#include "libmcx_main.h"

int _mcxDsrEntry(void) {
    int result;

    if (_mcxIntRestSize != 0) {
        _mcxCallFromC = 1;
        _mcxFastDsrEnt();
        _mcxCallFromC = 0;
        return 0;
    }
    _mcxCmdSeq++;
    result = _mcxStepSio();
    if (result != 0) {
        if (result == 1) {
            volatile unsigned short *sio;
            volatile unsigned int *interrupt;

            _mcxStat = 0x41;
            if (_mcxPass != 0) {
                _mcxChkRsrv(_mcxPort);
                _mcxStat = 2;
                _mcxPass--;
            }
            sio = D_000006F0;
            interrupt = D_000006F4;
            sio[5] = 0;
            interrupt[0] = ~0x80;
            interrupt[1] &= ~0x80;
            _mcxCmdSeq = 0;
            SysDeqIntRP(1, &_mcxTblDsrEnt);
        } else {
            volatile unsigned short *sio;
            volatile unsigned int *interrupt;

            sio = D_000006F0;
            interrupt = D_000006F4;
            sio[5] = 0;
            interrupt[0] = ~0x80;
            interrupt[1] &= ~0x80;
            _mcxStat = 0x21;
            _mcxCmdSeq = 0;
            SysDeqIntRP(1, &_mcxTblDsrEnt);
        }
    }
    return 0;
}
