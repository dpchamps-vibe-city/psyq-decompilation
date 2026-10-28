#include "common.h"
#include "libmcx.h"
#include "libmcx_command_setup.h"

static int func_00000124(int value);

static int func_00000124(int value) {
    switch (_mcxRxLen) {
    case 2:
        _mcxRestSize = 8;
        break;
    case 3:
        if ((value & 0xFF) != 0x5A) {
            return -1;
        }
        break;
    case 7:
        *_mcxPtrCmdBuf0 = value & 0xFF;
        break;
    case 8:
        *_mcxPtrCmdBuf0 = (*_mcxPtrCmdBuf0 << 8) + (value & 0xFF);
        break;
    case 9:
        *_mcxPtrCmdBuf1 = value & 0xFF;
        break;
    case 10:
        *_mcxPtrCmdBuf1 = (*_mcxPtrCmdBuf1 << 8) + (value & 0xFF);
        break;
    }
    return 0;
}
