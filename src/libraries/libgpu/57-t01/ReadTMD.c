#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

static s32 func_000004D4();
extern SVECTOR *B_00001888;
extern SVECTOR *B_0000188C;
extern void *B_00001890;

TMD_PRIM *ReadTMD(TMD_PRIM *tmdprim) {
    s32 temp_v0;

    temp_v0 = func_000004D4(B_00001890, tmdprim);
    if (temp_v0 < 0) {
        return NULL;
    }
    {
        tmdprim->v_ofs = B_00001888;
        tmdprim->n_ofs = B_0000188C;
        tmdprim->n0.vx = (s16) (u16) B_0000188C[tmdprim->norm0].vx;
        tmdprim->n0.vy = (s16) (u16) B_0000188C[tmdprim->norm0].vy;
        tmdprim->n0.vz = (s16) (u16) B_0000188C[tmdprim->norm0].vz;
        tmdprim->n1.vx = (s16) (u16) B_0000188C[tmdprim->norm1].vx;
        tmdprim->n1.vy = (s16) (u16) B_0000188C[tmdprim->norm1].vy;
        tmdprim->n1.vz = (s16) (u16) B_0000188C[tmdprim->norm1].vz;
        tmdprim->n2.vx = (s16) (u16) B_0000188C[tmdprim->norm2].vx;
        tmdprim->n2.vy = (s16) (u16) B_0000188C[tmdprim->norm2].vy;
        tmdprim->n2.vz = (s16) (u16) B_0000188C[tmdprim->norm2].vz;
        B_00001890 = (void *) ((u8 *) B_00001890 + temp_v0);
        tmdprim->n3.vx = (s16) (u16) B_0000188C[tmdprim->norm3].vx;
        tmdprim->n3.vy = (s16) (u16) B_0000188C[tmdprim->norm3].vy;
        tmdprim->n3.vz = (s16) (u16) B_0000188C[tmdprim->norm3].vz;
        tmdprim->x0.vx = (s16) (u16) B_00001888[tmdprim->vert0].vx;
        tmdprim->x0.vy = (s16) (u16) B_00001888[tmdprim->vert0].vy;
        tmdprim->x0.vz = (s16) (u16) B_00001888[tmdprim->vert0].vz;
        tmdprim->x1.vx = (s16) (u16) B_00001888[tmdprim->vert1].vx;
        tmdprim->x1.vy = (s16) (u16) B_00001888[tmdprim->vert1].vy;
        tmdprim->x1.vz = (s16) (u16) B_00001888[tmdprim->vert1].vz;
        tmdprim->x2.vx = (s16) (u16) B_00001888[tmdprim->vert2].vx;
        tmdprim->x2.vy = (s16) (u16) B_00001888[tmdprim->vert2].vy;
        tmdprim->x2.vz = (s16) (u16) B_00001888[tmdprim->vert2].vz;
        tmdprim->x3.vx = (s16) (u16) B_00001888[tmdprim->vert3].vx;
        tmdprim->x3.vy = (s16) (u16) B_00001888[tmdprim->vert3].vy;
        tmdprim->x3.vz = (s16) (u16) B_00001888[tmdprim->vert3].vz;
    }
    return tmdprim;
}
