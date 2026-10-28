#include "common.h"

static int func_000005D8(void);
extern volatile u_long *D_0000087C;

int DecDCToutSync(int mode) {
    int result;

    if (mode == 0) {
        result = func_000005D8();
    } else {
        result = (*D_0000087C >> 24) & 1;
    }
    return result;
}
