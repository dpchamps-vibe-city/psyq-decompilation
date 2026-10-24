#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void GsClearOt(unsigned short offset, unsigned short point, GsOT *otp) {
    otp->offset = offset & 0xFFFF;
    otp->point = point & 0xFFFF;
    otp->tag = (GsOT_TAG *) ((u8 *) ((void *) ((u8 *) otp->org + (4 << otp->length))) - 4);
    ClearOTagR((u_long *) otp->org, 1 << otp->length);
}
