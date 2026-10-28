#include "common.h"
#include "libmcx_cmd15.h"

static int func_00000104(void) {
    unsigned char value;

    if (_mcxPass != 0) {
        switch (_mcxCmdSeq) {
        case 2:
            return 0x52;
        case 5:
            return ((unsigned char *)&_mcxParam)[1];
        case 6:
            return ((unsigned char *)&_mcxParam)[0];
        default:
            return 0;
        }
    } else {
        switch (_mcxCmdSeq) {
        case 2:
            _mcxSum = 0;
            return 0x57;
        case 5:
            return ((unsigned char *)&_mcxParam)[1];
        case 6:
            return ((unsigned char *)&_mcxParam)[0];
        case 0x85:
            _mcxSum ^= ((unsigned char *)&_mcxFlag)[0];
            return _mcxFlag;
        case 0x86:
            return _mcxSum;
        case 0x87:
            return ((_mcxParam >> 8) ^ _mcxParam) & 0xFF;
        default:
            if (_mcxCmdSeq >= 7) {
                if (_mcxCmdSeq < 0x85) {
                    value = _mcxRxBuf[_mcxCmdSeq + 3];
                    _mcxSum ^= value;
                    return value;
                }
            }
            return 0;
        }
    }
}
