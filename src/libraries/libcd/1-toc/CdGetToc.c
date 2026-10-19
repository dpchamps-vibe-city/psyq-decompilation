#include "common.h"

static s32 CdGetToc2(s32 mode, void *loc);

s32 CdGetToc(void *loc) {
    return CdGetToc2(1, loc);
}
