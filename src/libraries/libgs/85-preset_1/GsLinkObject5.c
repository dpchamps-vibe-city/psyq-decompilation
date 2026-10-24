#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void GsLinkObject5(unsigned long tmd_base, GsDOBJ5 *objp, int n) {
    objp->tmd = (unsigned long *)(tmd_base + (n * 0x1C));
    objp->attribute = 0;
}
