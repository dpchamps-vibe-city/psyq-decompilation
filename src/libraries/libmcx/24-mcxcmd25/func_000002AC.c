#include "common.h"
#include "libmcx_cmd15.h"

static int func_000002AC(int value) {
    unsigned char c = value;

    if (_mcxPass) {
        switch (_mcxRxLen) {
        case 2:
            if ((c & 0xFF) == 8) {
                _mcxPass = 0;
                _mcxRestSize = 1;
                return 0;
            }
            _mcxRestSize = 0x8A;
            return 0;
        case 3:
            if ((c & 0xFF) != 0x5A) {
                return -3;
            }
            break;
        case 8:
            if ((c & 0xFF) != 0x5D) {
                return -8;
            }
            _mcxSum = 0;
            break;
        case 9:
            if ((c & 0xFF) != ((u8 *)&_mcxParam)[1]) {
                return -9;
            }
            _mcxSum ^= value;
            break;
        case 10:
            if ((c & 0xFF) != ((u8 *)&_mcxParam)[0]) {
                return -10;
            }
            _mcxSum ^= value;
            _mcxStartFastDsr(0, _mcxRxBuf + 10, 0x80, &_mcxSum);
            _mcxRestSize = 2;
            _mcxRxLen += 0x80;
            _mcxTxLen += 0x80;
            break;
        case 0x8B:
            if ((c & 0xFF) != _mcxSum) {
                return -0x8B;
            }
            break;
        case 0x8C:
            if ((c & 0xFF) != 0x47) {
                return -0x8C;
            }
            break;
        default:
            if ((unsigned)(_mcxRxLen - 11) < 0x80) {
                _mcxSum ^= c;
            }
            break;
        }
    } else {
        switch (_mcxRxLen) {
        case 2:
            if ((c & 0xFF) == 8) {
                _mcxRestSize = 1;
            } else {
                _mcxRestSize = 0x88;
            }
            break;
        case 3:
            if ((c & 0xFF) != 0x5A) {
                return -3;
            }
            break;
        case 5:
            _mcxStartFastDsr(1, _mcxRxBuf + 10, 0x7E, &_mcxSum);
            _mcxRestSize = 7;
            _mcxRxLen += 0x7E;
            _mcxTxLen += 0x7E;
            break;
        case 0x89:
            if ((c & 0xFF) != 0x5D) {
                return -0x89;
            }
            break;
        case 0x8A:
            if ((c & 0xFF) != 0x47) {
                return -0x8A;
            }
            break;
        }
    }
    return 0;
}
