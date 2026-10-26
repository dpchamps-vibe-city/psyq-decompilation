#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

/* Static state shared with GsLinkAnim's translation unit. */
extern u_long B_00000160;
extern u_long *B_00000164;
extern u_long *B_00000168;

u_long *GsScanAnim(u_long *addr, GsTYPEUNIT *ut) {
    if (addr) {
        B_00000164 = (u_long *)*((u_long *)(*(addr - 2)) + 2);
        B_00000160 = *B_00000164;
        B_00000160 &= 0x7fffffff;
        *B_00000164 = B_00000160;
        B_00000168 = B_00000164 + 1;
        return addr;
    }

    if (B_00000160 == 0)
        return 0;

    ut->ptr = B_00000168;
    ut->type = *B_00000168;
    B_00000168++;
    B_00000160--;
    return ut->ptr;
}
