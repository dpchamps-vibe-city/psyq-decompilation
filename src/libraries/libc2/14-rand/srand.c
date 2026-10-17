#include "common.h"

void srand(u32 arg0) {
    B_000000B0 = arg0;
}
