/* Original TU: library-input/psyq/LIB/LIBC2.LIB[28] STRSTR.OBJ
 * sha256: 3e4574892f7f1ce5d311ea039d8d11e0c6960dfad74277dae97df4d18c6495ba
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strstr
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

s8 *strstr(s8 *arg0, s8 *arg1) {
    s8 *p;
    s8 *q;
    s8 *start;
    s32 flag;

    p = arg0;
    flag = 0;
    q = arg1;
    start = arg0;
    while (*p != 0) {
        if (*p == *q) {
            q++;
            if (*q == 0) {
                return start;
            }
            if (flag == 0) {
                start = p;
                flag = 1;
            }
        } else {
            q = arg1;
            flag = 0;
        }
        p++;
    }
    return 0;
}
