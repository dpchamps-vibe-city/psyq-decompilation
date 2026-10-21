#include "common.h"


void DS_start_callback(void (*arg0)(u8, u8 *)) {
    B_000013A4 = arg0;
}
