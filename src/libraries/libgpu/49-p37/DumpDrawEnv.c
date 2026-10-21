#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

extern char RO_STR_00000220[];
extern char RO_STR_00000238[];
extern char RO_STR_00000248[];
extern char RO_STR_00000260[];
extern char RO_STR_0000026C[];
extern char RO_STR_00000278[];

void DumpDrawEnv(DRAWENV *env) {
    GPU_printf(RO_STR_00000220, env->clip.x, env->clip.y, env->clip.w, (s32) env->clip.h);
    GPU_printf(RO_STR_00000238, env->ofs[0], env->ofs[1]);
    GPU_printf(RO_STR_00000248, env->tw.x, env->tw.y, env->tw.w, (s32) env->tw.h);
    GPU_printf(RO_STR_00000260, env->dtd);
    GPU_printf(RO_STR_0000026C, env->dfe);
    GPU_printf(RO_STR_00000278, ((env->tpage) >> 7) & 0x003, ((env->tpage) >> 5) & 0x003, ((env->tpage) << 6) & 0x7c0, (((env->tpage) << 4) & 0x100) + (((env->tpage) >> 2) & 0x200));
}
