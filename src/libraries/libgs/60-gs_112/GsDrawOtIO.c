#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void GsDrawOtIO(GsOT *ot) {
    DrawOTagIO((u_long *) ot->tag);
}
