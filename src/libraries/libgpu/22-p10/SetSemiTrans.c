#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetSemiTrans(void *p, int abe) {
    u8 var_v0;

    if (abe != 0) {
        var_v0 = (*(u8 *) ((u8 *) p + 7)) | 2;
    } else {
        var_v0 = (*(u8 *) ((u8 *) p + 7)) & 0xFD;
    }
    (*(u8 *) ((u8 *) p + 7)) = var_v0;
}
