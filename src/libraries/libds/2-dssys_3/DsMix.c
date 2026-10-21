#include "common.h"

typedef struct {
    u8 val0;
    u8 val1;
    u8 val2;
    u8 val3;
} DslATV;

extern s32 CD_vol(u8 *arg0);

int DsMix(DslATV *vol) {
    CD_vol((u8 *)vol);
    return 1;
}
