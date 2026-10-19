#include "common.h"
#include <sys/types.h>
#include <libcd.h>

int CdGetToc2(int mode, CdlLOC *loc);

int CdGetToc(CdlLOC *loc) {
    return CdGetToc2(1, loc);
}
