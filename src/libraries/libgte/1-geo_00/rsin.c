#include "common.h"

extern s16 rsin_tbl[];

extern int sin_1(int a);

int rsin(int a) {
    if (a < 0) {
        return -sin_1(-a & 0xFFF);
    }
    return sin_1(a & 0xFFF);
}
