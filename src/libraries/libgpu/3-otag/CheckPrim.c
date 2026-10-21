#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

extern char RO_STR_00000488[];
extern char RO_STR_0000048C[];
extern char RO_STR_000004C0[];
extern char *D_STR_000004F0[];
extern u_char D_00000550[];

int CheckPrim(char *s, u_long *p) {
    u_char len;
    char *name;
    u_int code;
    u_int code2;

    code = p[1] >> 24;
    if ((u_char)code == 2) {
        len = 3;
    } else if ((code - 0x20) < 0x60) {
        len = D_00000550[((u_char)code - 0x20) / 4];
    } else {
        len = 0;
    }
    if (len != 0 && len != (u_char)(p[0] >> 24)) {
        code2 = p[1] >> 24;
        if ((u_char)code2 == 2) {
            name = RO_STR_00000488;
        } else if ((code2 - 0x20) < 0x60) {
            name = D_STR_000004F0[((u_char)code2 - 0x20) / 4];
        } else {
            name = RO_STR_0000048C;
        }
        GPU_printf(RO_STR_000004C0, s, p, name, (u_char)(p[0] >> 24));
        return -1;
    }
    return 0;
}
