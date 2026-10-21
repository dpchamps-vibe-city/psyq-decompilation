#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <strings.h>

extern s32 D_00000D30;
extern s32 D_00000D34;

void SetDumpFnt(int id) {
    if ((id >= 0) && (D_00000D30 >= id)) {
        D_00000D34 = id;
        GPU_printf = (int (*)(char *, ...))FntPrint;
    }
}
