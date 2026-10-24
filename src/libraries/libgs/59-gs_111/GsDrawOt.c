#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void GsDrawOt(GsOT *ot) {
    DrawOTag((u_long *) ot->tag);
}
