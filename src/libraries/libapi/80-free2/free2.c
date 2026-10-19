/* Original TU: FREE2.OBJ (LIBAPI.LIB[80]) */
#include "common.h"

extern u32 *_Candidate;

void free2(void *ptr) {
    u32 *p;

    p = (u32 *)((u8 *)ptr - 4);
    *p |= 1;
    if (p < _Candidate) {
        _Candidate = p;
    }
}
