#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern u8 GEnv;

u32 func_000016D8();              /* static */
u32 func_00001770(s16 arg0, s16 arg1);              /* static */
u32 func_00001808();              /* static */
static u32 func_000016B8(s32 arg0, s32 arg1, s32 arg2);
u32 func_00001824(RECT *arg0);                      /* static */

static void func_00001448(DR_ENV *arg0, DRAWENV *arg1) {
    DR_ENV *p;
    DRAWENV *e;
    RECT r;
    s32 len;

    e = arg1;
    p = arg0;

    p->code[0] = func_000016D8(e->clip.x, e->clip.y);
    p->code[1] = func_00001770((s16) (((u16) e->clip.w + (u16) e->clip.x) - 1), (s16) (((u16) e->clip.y + (u16) e->clip.h) - 1));
    p->code[2] = func_00001808(e->ofs[0], e->ofs[1]);
    p->code[3] = func_000016B8(e->dfe, e->dtd, e->tpage);
    p->code[4] = func_00001824(&e->tw);
    p->code[5] = 0xE6000000;
    len = 7;
    if (e->isbg != 0) {
        r.x = e->clip.x;
        r.y = e->clip.y;
        r.w = e->clip.w;
        r.h = e->clip.h;
        r.w = r.w < 0 ? 0 : (r.w > *(s16 *) ((u8 *) &GEnv + 4) - 1 ? *(s16 *) ((u8 *) &GEnv + 4) - 1 : r.w);
        r.h = r.h < 0 ? 0 : (r.h > *(s16 *) ((u8 *) &GEnv + 6) - 1 ? *(s16 *) ((u8 *) &GEnv + 6) - 1 : r.h);
        if ((r.x & 0x3F) || (r.w & 0x3F)) {
            r.x -= e->ofs[0];
            r.y -= e->ofs[1];
            *((s32 *) ((u8 *) p + (len * 4))) = (e->b0 << 0x10) | 0x60000000 | (e->g0 << 8) | e->r0;
            len++;
            *((s32 *) ((u8 *) p + (len * 4))) = *(s32 *) &r.x;
            len++;
            *((s32 *) ((u8 *) p + (len * 4))) = *(s32 *) &r.w;
            len++;
        } else {
            *((s32 *) ((u8 *) p + (len * 4))) = (e->b0 << 0x10) | 0x02000000 | (e->g0 << 8) | e->r0;
            len++;
            *((s32 *) ((u8 *) p + (len * 4))) = *(s32 *) &r.x;
            len++;
            *((s32 *) ((u8 *) p + (len * 4))) = *(s32 *) &r.w;
            len++;
        }
    }
    (*(s8 *) ((u8 *) p + 3)) = (s8) (len - 1);
}
