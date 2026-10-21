#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

int GetTimSize(u_char *sjis) {
    int size;
    int c;
    int v;

    size = 0;
    while ((c = *sjis) != 0 && size < 0x100) {
        if (c == 0x0A) {
            size = (size / 16 + 1) * 16;
            sjis++;
        } else {
            if ((u32) ((c + 0x7F) & 0xFF) < 0x18)
                sjis += 2;
            else
                sjis++;
            size++;
        }
    }

    if (size < 0x10)
        v = size * 0x20;
    else
        v = ((size - 1) / 16 + 1) * 0x200;

    return (v + 0x10) * 4;
}
