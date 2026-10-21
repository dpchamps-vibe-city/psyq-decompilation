#include "common.h"
#include <sys/types.h>
#include <libds.h>

extern volatile u8 *D_00000170;
extern volatile u8 *D_00000174;
extern volatile s32 *D_00000178;
extern volatile s32 *D_0000017C;
extern volatile s32 *D_00000180;
extern volatile s32 *D_00000184;
extern volatile u32 *D_00000188;
extern volatile s32 *D_0000018C;

s32 CD_getsector(void *arg0, s32 arg1) {
    *D_00000170 = 0;
    *D_00000174 = 0x80;
    *D_0000017C = 0x20943;
    *D_00000178 = 0x1323;
    *D_00000180 |= 0x8000;
    *D_00000188 = (u32)arg0;
    *D_0000018C = arg1 | 0x10000;
    do {

    } while (!(*D_00000170 & 0x40));
    *D_00000184 = 0x11000000;
    if (*D_00000184 & 0x01000000) {
        do {

        } while (*D_00000184 & 0x01000000);
    }
    *D_00000178 = 0x1325;
    return 0;
}
