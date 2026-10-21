#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

extern char RO_STR_00000488[];
extern char RO_STR_0000048C[];
extern char RO_STR_00000490[];
extern char RO_STR_000004A0[];
extern char RO_STR_000004A8[];
extern char RO_STR_000004B4[];
extern char RO_STR_000004B8[];
extern char *D_STR_000004F0[];

extern int CheckPrim(char *, u_long *);

void DumpOTag(u_long *p) {
    u_char *cp;
    char *name;
    int n;
    u_int code;
    u_int code2;

    n = 1;
    GPU_printf(RO_STR_00000490, 0);
    while ((*p & 0xFFFFFF) != 0xFFFFFF) {
        cp = (u_char *)p;
        if (cp[3] == 0) {
            cp = (u_char *)((*p & 0xFFFFFF) | 0x80000000);
            if (cp[3] != 0) {
                GPU_printf(RO_STR_000004A0, n);
            }
            n++;
        } else {
            CheckPrim(RO_STR_000004A8, p);
            code = p[1] >> 24;
            if ((u_char)code == 2) {
                name = RO_STR_00000488;
            } else if ((code - 0x20) < 0x60) {
                name = D_STR_000004F0[((u_char)code - 0x20) / 4];
            } else {
                name = RO_STR_0000048C;
            }
            GPU_printf(RO_STR_000004B4, name);
        }
        p = (u_long *)((*p & 0xFFFFFF) | 0x80000000);
    }
    CheckPrim(RO_STR_000004A8, p);
    code2 = p[1] >> 24;
    if ((u_char)code2 == 2) {
        name = RO_STR_00000488;
    } else if ((code2 - 0x20) < 0x60) {
        name = D_STR_000004F0[((u_char)code2 - 0x20) / 4];
    } else {
        name = RO_STR_0000048C;
    }
    GPU_printf(RO_STR_000004B8, name);
}
