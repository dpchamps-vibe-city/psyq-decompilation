#include "common.h"
#include <sys/types.h>

void GsInitVcount(void) {
    SetRCnt(0xF2000001U, -1U, 0x2000);
    StartRCnt(0xF2000001U);
}
