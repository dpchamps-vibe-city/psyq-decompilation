/* Libcd.lib S_021.OBJ */
#include "common.h"

s32 CD_getsector();

s32 CdGetSector(void)
{
    return CD_getsector() == 0;
}
