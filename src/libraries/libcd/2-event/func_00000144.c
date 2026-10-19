#include "common.h"
#include <libapi.h>

static void func_00000144(void) __asm__("$Lfunc_00000144");

static void func_00000144(void) {
    DeliverEvent(0xF0000003, 0x20);
}
