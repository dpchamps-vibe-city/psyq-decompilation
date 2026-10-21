#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetDrawTPage(DR_TPAGE *p, int dfe, int dtd, int tpage) {
    setlen(p, 1);
    p->code[0] = _get_mode(dfe, dtd, tpage);
}
