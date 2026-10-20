#include "common.h"
#include <sys/types.h>
#include <libds.h>

extern volatile u8 *D_00000160 __asm__("$LD_00000160");
extern volatile u8 *D_00000164 __asm__("$LD_00000164");
extern volatile s32 *D_00000168 __asm__("$LD_00000168");
extern volatile s32 *D_0000016C __asm__("$LD_0000016C");
extern volatile s32 *D_00000170 __asm__("$LD_00000170");
extern volatile s32 *D_00000174 __asm__("$LD_00000174");
extern volatile void **D_00000178 __asm__("$LD_00000178");
extern volatile s32 *D_0000017C __asm__("$LD_0000017C");

s32 CD_getsector2(void *arg0, s32 arg1) {
    volatile s32 sp0;

    *D_00000160 = 0;
    *D_00000164 = 0x80;
    *D_0000016C = 0x21020843;
    *D_00000168 = 0x1325;
    *D_00000170 |= 0x8000;
    *D_00000178 = arg0;
    *D_0000017C = arg1 | 0x10000;
    while (!(*D_00000160 & 0x40)) {
    }
    *D_00000174 = 0x11400100;
    sp0 = *D_00000174;
    return 0;
}
