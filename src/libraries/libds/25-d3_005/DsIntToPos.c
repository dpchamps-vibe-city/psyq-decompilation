#include "common.h"
#include <sys/types.h>
#include <libds.h>

DslLOC *DsIntToPos(int i, DslLOC *p) {
    int t = i + 0x96;
    int v = t / 75;
    int s = t % 75;
    int h = v / 60;
    int m = v % 60;

    p->sector = ((s / 10) * 0x10) + (s % 10);
    p->second = ((m / 10) * 0x10) + (m % 10);
    p->minute = ((h / 10) * 0x10) + (h % 10);
    return p;
}
