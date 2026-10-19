#include "common.h"

extern s32 StEndFrame;
extern s32 StSTART_FLAG;
extern s32 StStartFrame;

void StSetMask(s32 arg0, s32 arg1, s32 arg2) {
    StSTART_FLAG = arg0;
    StStartFrame = arg1;
    StEndFrame = arg2;
}
