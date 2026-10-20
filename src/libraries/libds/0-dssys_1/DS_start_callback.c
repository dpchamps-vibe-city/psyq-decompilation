#include "common.h"

extern void (* volatile B_000013A4)(u8, u8 *) __asm__("$LB_00001398+12");

void DS_start_callback(void (*arg0)(u8, u8 *)) {
    B_000013A4 = arg0;
}
