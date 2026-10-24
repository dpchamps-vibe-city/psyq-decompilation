#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern MATRIX _LC;

void func_00000520(MATRIX *mp) {
    _LC = *mp;
    SetColorMatrix(mp);
}
