#include "common.h"

extern void (* volatile B_00001398)(u8, u8 *);

void DS_vsync_callback(void (*arg0)(u8, u8 *)) {
    B_00001398 = arg0;
}
