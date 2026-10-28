#include "common.h"
#include "libpad-internal.h"
#include "libpad-mtap.h"

static int func_000010F8(PadInfo2 *info) {
    PadInfo2 *child;
    int i;

    if (info->exId == 0) {
        return 1;
    }
    if (info->child != 0) {
        if (info->commandState != 0xFF) {
            return 1;
        }
        child = info->root->child;
        for (i = 0; i < 4; i++) {
            if (child->commandState != 0xFF && child->commandState != 0) {
                return 1;
            }
            child++;
        }
        return 0;
    }
    i = 0;
    if (info->root->commandState != 0xFF ||
        info->commandState != info->root->commandState) {
        i = 1;
    }
    return i;
}
