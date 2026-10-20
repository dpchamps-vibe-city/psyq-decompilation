#include "common.h"
#include <sys/types.h>
#include <libcd.h>

extern CdlLOC CD_pos;

CdlLOC *CdLastPos(void) {
    return &CD_pos;
}
