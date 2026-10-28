#include "common.h"
#include <sys/types.h>
#include <libpress.h>

static void func_00000428(u32 *data, u32 words);

void DecDCTin(u_long *buf, int mode) {
    if (mode & 0x1) {
        *buf &= ~0x08000000;
    } else {
        *buf |= 0x08000000;
    }
    if (mode & 0x2) {
        *buf |= 0x02000000;
    } else {
        *buf &= ~0x02000000;
    }
    func_00000428((u32 *)buf, *(u_short *)buf);
}
