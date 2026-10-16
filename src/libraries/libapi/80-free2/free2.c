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
