#include "common.h"

extern int ResetCallback(void);
static void func_00000338(int mode);

void DecDCTReset(int mode) {
    if (mode == 0) {
        ResetCallback();
    }
    func_00000338(mode);
}
