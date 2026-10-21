#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void DrawOTagIO(u_long *p) {
    u_long *p1;
    u_char *p2;

    p1 = p;
    while ((*p1 & 0xFFFFFF) != 0xFFFFFF) {
        p2 = (u_char *)p1;
        if (p2[3] != 0) {
            DrawPrim(p1);
        }
        p1 = (u_long *)((*p1 & 0xFFFFFF) | 0x80000000);
    }
    p2 = (u_char *)p1;
    if (p2[3] != 0) {
        DrawPrim(p1);
    }
}
