#include "common.h"
#include "libmcx_main.h"
extern int _mcxFuncNo;

#include "libmcx_cmd15.h"

int McxSync(int mode, long *cmd, long *stat) {
    if (_mcxFuncNo == 0 || _mcxStat == 1) {
        if (cmd != 0) {
            *cmd = 0;
        }
        if (stat != 0) {
            *stat = 0;
        }
        return -1;
    }
    if (mode == 0) {
        while (_mcxStat < 5) {
        }
    }
    if (cmd != 0) {
        *cmd = _mcxFuncNo;
    }
    if (stat != 0) {
        switch (_mcxStat) {
        case 2:
        case 4:
            *stat = 0;
            return 0;
        case 0x11:
            if (_mcxTxLen == 1) {
                *stat = _mcxTxLen;
            } else {
                *stat = 2;
            }
            break;
        case 0x21:
            *stat = 2;
            break;
        default:
            if (_mcxRxBuf[1] == 8) {
                *stat = 3;
            } else {
                *stat = 0;
            }
            break;
        }
    } else {
        if (_mcxStat == 2 || _mcxStat == 4) {
            return 0;
        }
    }
    _mcxFuncNo = 0;
    return 1;
}
