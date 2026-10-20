#include "common.h"

s32 CD_init(void);
void CD_initintr(void);
s32 CD_initvol(void);

s32 CdReset(s32 mode) {
    if (mode == 2) {
        CD_initintr();
        return 1;
    }
    if (CD_init() != 0) {
        return 0;
    }
    if (mode == 1) {
        if (CD_initvol() != 0) {
            return 0;
        }
    }
    return 1;
}
