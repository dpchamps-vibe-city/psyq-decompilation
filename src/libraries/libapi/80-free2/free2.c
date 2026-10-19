/* Original TU: library-input/psyq/LIB/LIBAPI.LIB[80] FREE2.OBJ
 * sha256: d5443c97f85f8cad1469df9839a53478bb8a4e94f934a6592c3cac2ae79d4132
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: free2
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

extern u32 *_Candidate;

void free2(void *arg0) {
    u32 *p;

    p = (u32 *)((u8 *)arg0 - 4);
    *p |= 1;
    if (p < _Candidate) {
        _Candidate = p;
    }
}
