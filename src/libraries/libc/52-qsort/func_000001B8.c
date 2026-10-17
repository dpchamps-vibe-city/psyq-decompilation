#include "common.h"
#include "52-qsort.h"

static void func_000001B8(void *left, void *right, u32 size) {
    unsigned char tmp;
    u32 i;

    for (i = 0; i < size; i++) {
        tmp = ((unsigned char *)left)[i];
        ((unsigned char *)left)[i] = ((unsigned char *)right)[i];
        ((unsigned char *)right)[i] = tmp;
    }
}
