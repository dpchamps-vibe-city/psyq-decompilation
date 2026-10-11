#include "common.h"

void *GsU_00000000(u16 **arg0) {
    u16 *temp_v1;

    temp_v1 = *arg0;
    return (void *) ((u8 *) temp_v1 + (*temp_v1 * 4));
}
