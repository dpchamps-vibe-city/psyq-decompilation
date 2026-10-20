#include "common.h"
#include <sys/types.h>
#include <libcd.h>

extern s32 CD_cw(s32 com, u8 *param, u8 *result, s32 mode);
extern void (*CD_cbsync)(u8, u8 *);
extern u8 CD_status;
extern s32 LD_00000430[] asm("$LD_00000430");

int CdControlF(u_char com, u_char *param) {
    void (*saved)(u8, u8 *);
    s32 i;
    s32 ret;
    s32 c;
    s32 end;
    s32 one;
    s32 *table;
    s32 *base;

    c = com & 0xFF;
    base = LD_00000430;
    saved = CD_cbsync;
    for (i = 3, one = 1, table = base + c, ret = 0, end = -1; i != end; i--) {
        CD_cbsync = 0;
        if ((c != one) && (CD_status & 0x10)) {
            CD_cw(1, 0, 0, 0);
        }
        if (param != 0) {
            if (*table != 0) {
                if (CD_cw(2, param, 0, 0) != 0) {
                    continue;
                }
            }
        }
        CD_cbsync = saved;
        if (CD_cw(com, param, 0, 1) == 0) {
            goto done;
        }
    }
    CD_cbsync = saved;
    ret = -1;
done:
    return ret + 1;
}
