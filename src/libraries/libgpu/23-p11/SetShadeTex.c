#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetShadeTex(void *p, int tge) {
    u8 var_v0;

    if (tge != 0) {
        var_v0 = (*(u8 *) ((u8 *) p + 7)) | 1;
    } else {
        var_v0 = (*(u8 *) ((u8 *) p + 7)) & 0xFE;
    }
    (*(u8 *) ((u8 *) p + 7)) = var_v0;
}
