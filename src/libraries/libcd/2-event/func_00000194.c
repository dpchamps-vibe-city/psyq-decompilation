#include "common.h"
#include <libapi.h>

static void func_00000194(void) __asm__("$Lfunc_00000194");

static void func_00000194(void) {
    DeliverEvent(0xF0000003, 0x40);
}
