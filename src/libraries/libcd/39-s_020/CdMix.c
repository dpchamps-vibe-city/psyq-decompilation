#include "common.h"
#include <sys/types.h>
#include <libcd.h>

s32 CD_vol(u8 *arg0);

int CdMix(CdlATV *vol) {
    CD_vol((u8 *)vol);
    return 1;
}
