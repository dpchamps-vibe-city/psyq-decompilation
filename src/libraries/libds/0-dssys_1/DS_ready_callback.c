#include "common.h"

extern void (* volatile B_000013A0)(u8, u8 *);

void DS_ready_callback(void (*arg0)(u8, u8 *)) {
    B_000013A0 = arg0;
}
