#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

extern volatile u_long *D_00000290;
extern volatile s32 *D_00000294;
extern volatile u_long *D_00000298;
extern volatile s32 *D_000002A0;

void _GPU_ResetCallback(void);

void ContinueDraw(u_long *insaddr, u_long *contaddr) {
    u_long *p;
    u_long *q;

    _GPU_ResetCallback();
    if (insaddr != 0) {
        if (contaddr != 0) {
            q = insaddr;
            p = insaddr;
            while ((*(u_long *)((*p & 0xFFFFFF) | 0x80000000) & 0xFFFFFF) != 0xFFFFFF) {
                q = p;
                p = (u_long *)((*p & 0xFFFFFF) | 0x80000000);
            }
            *q = (*q & 0xFF000000) | ((u_long)contaddr & 0xFFFFFF);
        }
    } else {
        if (contaddr == 0) {
            return;
        }
        insaddr = contaddr;
    }
    *D_000002A0 = 0x04000002;
    *D_00000290 = (u_long)insaddr;
    *D_00000294 = 0;
    *D_00000298 = 0x01000401;
}
