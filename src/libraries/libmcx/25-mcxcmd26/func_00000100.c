#include "common.h"
#include "libmcx_command_bytes.h"

static int func_00000100(void) {
    switch (_mcxCmdSeq) {
    case 2:
        return 0x53;
    default:
        return 0;
    }
}
