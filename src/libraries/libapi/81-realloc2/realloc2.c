#include "common.h"

extern void free2(void *);
extern u8 *malloc2(s32);
static u8 *func_000000F8(u8 *arg0, s32 arg1);
static u8 *func_00000280(u8 *arg0, u8 *arg1, s32 arg2);

u8 *realloc2(u8 *ptr, s32 size) {
    u8 *newptr;

    if (ptr == 0) {
        newptr = malloc2(size);
    } else if (size != 0) {
        newptr = func_000000F8(ptr, size);
        if (newptr == 0) {
            newptr = malloc2(size);
            if (newptr != 0) {
                func_00000280(ptr, newptr, size);
                free2(ptr);
            }
        }
    } else {
        free2(ptr);
    }
    return newptr;
}
