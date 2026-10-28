#include "common.h"
#include "libpad-internal.h"

void PadInitDirect(unsigned char *port1, unsigned char *port2) {
    PadInfo2 *info;
    u8 *response;
    int i;
    int j;

    _padIntExec = 0;
    _padModeMtap = 0;
    _padInitDirPort();

    _padInfoDir[0].commandBuffer = port1;
    _padInfoDir[1].commandBuffer = port2;
    info = _padInfoDir;
    for (i = 0; i < 2; i++, info++) {
        info->child = 0;
        info->root = info;
        info->commandBuffer[0] = 0xFF;
        info->commandBuffer[1] = 0;
        response = info->actAlignResponse;
        for (j = 5; j >= 0; j--) {
            *response++ = 0xFF;
        }
    }
    _padIntExec = 1;
}
