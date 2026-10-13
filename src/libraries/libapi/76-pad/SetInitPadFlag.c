#include "library/api-pad.h"

void SetInitPadFlag(s32 flag) {
    D_00000300 = flag;
}
