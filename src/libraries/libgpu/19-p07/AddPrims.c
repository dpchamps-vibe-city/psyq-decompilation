#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void AddPrims(void *ot, void *p0, void *p1) {
    setaddr(p1, getaddr(ot));
    setaddr(ot, p0);
}
