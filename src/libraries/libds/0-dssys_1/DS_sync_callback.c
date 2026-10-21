#include "common.h"


void DS_sync_callback(void (*arg0)(u8, u8 *)) {
    B_0000139C = arg0;
}
