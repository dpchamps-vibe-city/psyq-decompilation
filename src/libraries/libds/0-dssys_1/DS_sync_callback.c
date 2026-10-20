#include "common.h"

extern void (* volatile B_0000139C)(u8, u8 *);

void DS_sync_callback(void (*arg0)(u8, u8 *)) {
    B_0000139C = arg0;
}
