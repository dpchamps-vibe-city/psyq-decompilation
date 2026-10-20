#include "common.h"
#include <sys/types.h>
#include <libgte.h>

extern s16 GsORGOFSX;
extern s16 GsORGOFSY;

void gte_init(void) {
    InitGeom();
    SetFarColor(0, 0, 0);
    SetGeomOffset(0, 0);
    GsORGOFSY = 0;
    GsORGOFSX = 0;
}
