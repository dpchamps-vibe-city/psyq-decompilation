#include "common.h"

extern void (*GlobalCallback)(u8, u8 *);

void func_00001440(u8 arg0, u8 *arg1) {
    if (((void (**)(u8, u8 *))&GlobalCallback)[2] != 0) {
        ((void (**)(u8, u8 *))&GlobalCallback)[2](arg0 & 0xFF, arg1);
    }
}
