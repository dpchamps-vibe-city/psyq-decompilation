#include "common.h"

extern s32 CD_read_dma_mode;

s32 CdReadMode(s32 arg0) {
    s32 temp_v0;

    temp_v0 = CD_read_dma_mode;
    CD_read_dma_mode = arg0;
    return temp_v0;
}
