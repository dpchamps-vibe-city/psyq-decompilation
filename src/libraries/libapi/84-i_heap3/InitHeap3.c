#include "common.h"

extern u32 *_freep;

void InitHeap3(u32 *head, u32 size) {
    u32 *p;

    if (head == 0 || size == 0) {
        return;
    }
    if (size & 7) {
        size = size - 1;
        while (size & 7) {
            size = size - 1;
        }
    }
    p = (u32 *)((u8 *)head + size);
    p[-2] = (u32)head;
    p -= 2;
    p[1] = 0;
    head[0] = (u32)p;
    _freep = head;
    head[1] = ((size + 7) >> 3) - 1;
}
