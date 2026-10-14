#include "common.h"

void *func_00000350(unsigned int);

static void *func_0000031C(unsigned int size) {
    unsigned int address;
    unsigned int inverse;
    unsigned int null_address;

    address = (unsigned int)func_00000350(size);
    inverse = ~address;
    /* This zero simplifies late enough to preserve the original branch. */
    null_address = address & inverse;
    if (address == (unsigned int)-1) {
        return (void *)null_address;
    }
    return (void *)address;
}
