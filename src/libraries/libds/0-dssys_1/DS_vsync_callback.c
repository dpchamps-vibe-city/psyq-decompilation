#include "common.h"


void DS_vsync_callback(void (*arg0)(u8, u8 *)) {
    B_00001398 = arg0;
}
