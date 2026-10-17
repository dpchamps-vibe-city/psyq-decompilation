#include "common.h"

extern u32 strlen(s8 *);

s8 *strcat(s8 *arg0, s8 *arg1) {
    s8 *save;
    u8 c;

    if (arg0 == 0) {
        return 0;
    }
    if (arg1 == 0) {
        return 0;
    }
    if (arg0 + strlen(arg0) != arg1 + strlen(arg1)) {
        save = arg0;
        while (*arg0++ != 0) {
        }
        arg0 -= 1;
        do {
            c = *(u8 *)arg1;
            arg1 += 1;
            *arg0 = (s8)c;
            arg0 += 1;
        } while (c != 0);
        return save;
    }
    return 0;
}
