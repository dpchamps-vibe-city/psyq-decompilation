#include "common.h"

void _padWaitRXready(void) {
    do {

    } while (!(D_00001F70->status & 2));
}
