#include "common.h"
#include "libpad-internal.h"
#include "libpad-mtap.h"

void PadInitMtap(unsigned char *port1, unsigned char *port2) {
    PadInfo2 *info;
    PadInfo2 *child;
    u8 *response;
    int i;
    int j;
    int k;
    int off1;
    int off2;

    _padIntExec = 0;
    _padModeMtap = 1;
    _padInitMtapPort();

    _padInfoDir[0].commandBuffer = port1;
    _padInfoDir[1].commandBuffer = port2;
    info = _padInfoDir;
    for (i = 0; i < 2; i++, info++) {
        info->root = info;
        info->commandBuffer[0] = 0xFF;
        info->commandBuffer[1] = 0;
        _mtapLastResult[i] = 0;
        response = info->actAlignResponse;
        for (j = 5; j >= 0; j--) {
            *response++ = 0xFF;
        }
        child = info->child;
        for (k = 0, off2 = 3, off1 = 2; k < 4;
             off2 += 8, off1 += 8, k++, child++) {
            child->root = info;
            child->commandBuffer = info->commandBuffer + off1;
            child->currentCommand = 0xFF;
            child->pad35[1] = 0;
            child->actSize = 0;
            child->commandBuffer[0] = 0xFF;
            child->commandBuffer[1] = 0;
            *(u8 **)&child->pad3A[2] = *(u8 **)&info->pad3A[2] + off1;
            *(u8 **)&child->pad3A[6] = *(u8 **)&info->pad3A[6] + off2;
            response = child->actAlignResponse;
            for (j = 5; j >= 0; j--) {
                *response++ = 0xFF;
            }
        }
    }
    _padIntExec = 1;
}
