#include "common.h"
#include <sys/types.h>
#include <libpress.h>

static s32 func_00000544(void);
static u32 func_0000066C(void);

int DecDCTinSync(int mode) {
    int result;

    if (mode == 0) {
        result = func_00000544();
    } else {
        result = (func_0000066C() >> 29) & 1;
    }
    return result;
}
