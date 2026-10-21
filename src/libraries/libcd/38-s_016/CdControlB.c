#include "common.h"
#include <sys/types.h>
#include <libcd.h>

extern s32 CD_cw(s32 com, u8 *param, u8 *result, s32 mode);
extern void (*CD_cbsync)(u8, u8 *);
extern u8 CD_status;
extern s32 D_00000430[];
extern s32 CD_sync(s32 mode, u8 *result);

int CdControlB(u_char com, u_char *param, u_char *result) {
    void (*saved)(u8, u8 *);
    s32 i;
    s32 ret;
    s32 c;
    s32 end;
    s32 one;
    s32 *table;
    s32 *base;

    c = com & 0xFF;
    base = D_00000430;
    saved = CD_cbsync;
    for (i = 3, one = 1, table = base + c, end = -1; i != end; i--) {
        CD_cbsync = 0;
        if ((c != one) && (CD_status & 0x10)) {
            CD_cw(1, 0, 0, 0);
        }
        if (param != 0) {
            if (*table != 0) {
                if (CD_cw(2, param, result, 0) != 0) {
                    continue;
                }
            }
        }
        CD_cbsync = saved;
        if (CD_cw(com, param, result, 0) == 0) {
            ret = 0;
            goto done;
        }
    }
    CD_cbsync = saved;
    ret = -1;
done:
    if (ret != 0) {
        return 0;
    }
    return CD_sync(0, result) == 2;
}
