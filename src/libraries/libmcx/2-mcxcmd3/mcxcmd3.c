/* Original TU: library-input/psyq/LIB/LIBMCX.LIB[2] MCXCMD3.OBJ
 * sha256: 992bffad1621a40c216399fe0abdc60b1bb91bb3f39872899143b4a7227f0d98
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: _mcxRxRestLen
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

extern s32 _mcxRestSize;
extern s32 _mcxRxLen;

s32 _mcxRxRestLen(s32 arg0) {
    if (_mcxRxLen == 3) {
        _mcxRestSize = arg0 & 0xFF;
    }
    return 0;
}
