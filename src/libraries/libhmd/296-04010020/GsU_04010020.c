#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

/* VtxMIMe primitive driver — 04010020.C lines 163-167 */
u_long *GsU_04010020(GsARGUNIT *sp)
{
    return func_00000068((GsARGUNIT_VNMIMe *)sp,
        ((GsARGUNIT_VNMIMe *)sp)->vert_sect);
}
