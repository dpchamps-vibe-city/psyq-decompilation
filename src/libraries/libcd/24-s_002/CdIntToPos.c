#include "common.h"
#include <sys/types.h>
#include <libcd.h>

CdlLOC *CdIntToPos(int i, CdlLOC *p) {
    i += 150;
    p->sector = (i % 75) / 10 * 16 + (i % 75) % 10;
    i /= 75;
    p->second = (i % 60) / 10 * 16 + (i % 60) % 10;
    i /= 60;
    p->minute = (i / 10) * 16 + i % 10;
    return p;
}
