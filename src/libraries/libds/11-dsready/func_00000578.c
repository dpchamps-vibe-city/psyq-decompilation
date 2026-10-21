#include "common.h"

void func_00000578(u8 arg0, u8 *arg1) {
    if ((arg0 & 0xFF) == 2) {
        DsReadyCallback(func_0000016C);
    }
}
