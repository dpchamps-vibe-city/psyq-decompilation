/* Original TU: Libcd.lib S_003.OBJ, CdStatus */
#include "common.h"

extern u8 CD_status;

int CdStatus(void) {
    return CD_status;
}
