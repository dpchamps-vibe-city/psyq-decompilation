#include "common.h"
#include <sys/types.h>
#include <libds.h>

u8 *DS_lastpos(void);

DslLOC *DsLastPos(DslLOC *p) {
    if (p != 0) {
        *p = *(DslLOC *)DS_lastpos();
        return p;
    }
    return (DslLOC *)DS_lastpos();
}
