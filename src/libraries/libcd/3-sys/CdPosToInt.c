#include "common.h"
#include <sys/types.h>
#include <libcd.h>

int CdPosToInt(CdlLOC *p) {
    return ((p->minute / 16 * 10 + p->minute % 16) * 60 +
            (p->second / 16 * 10 + p->second % 16)) * 75 +
           (p->sector / 16 * 10 + p->sector % 16) - 150;
}
