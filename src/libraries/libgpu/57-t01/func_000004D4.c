#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern char RO_STR_000017FC[];
extern char RO_STR_00001804[];
extern char RO_STR_0000180C[];
extern char RO_STR_00001814[];
extern char RO_STR_0000181C[];
extern char RO_STR_00001820[];
extern char RO_STR_00001824[];
extern char RO_STR_0000182C[];
extern char RO_STR_00001834[];
extern char RO_STR_0000183C[];
extern char RO_STR_00001844[];
extern char RO_STR_0000184C[];
extern char RO_STR_00001854[];
extern char RO_STR_00001858[];
extern char RO_STR_0000185C[];
extern char RO_STR_00001864[];
extern char RO_STR_0000186C[];

static s32 func_000004D4(void *arg0, TMD_PRIM *arg1) {
    u32 temp_v0;
    u32 temp_v1;

    memset(arg1, 0, 0x78);
    temp_v0 = *(u32 *) ((u8 *) arg0 + 0);
    temp_v1 = temp_v0 & 0xFDFFFFFF;
    arg1->id = temp_v0;
    switch (temp_v1) {
    case 0x20020304:
    case 0x20000304:
        if (GetGraphDebug() == 2) {
            printf(RO_STR_000017FC);
        }
        arg1->r0 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g0 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b0 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->r1 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g1 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b1 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->r2 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g2 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b2 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->vert0 = *(u16 *) ((u8 *) arg0 + 0xA);
        arg1->vert1 = *(u16 *) ((u8 *) arg0 + 0xC);
        arg1->vert2 = *(u16 *) ((u8 *) arg0 + 0xE);
        arg1->norm0 = *(u16 *) ((u8 *) arg0 + 0x8);
        arg1->norm1 = *(u16 *) ((u8 *) arg0 + 0x8);
        arg1->norm2 = *(u16 *) ((u8 *) arg0 + 0x8);
        return 0x10;
    case 0x30020406:
    case 0x30000406:
        if (GetGraphDebug() == 2) {
            printf(RO_STR_00001804);
        }
        arg1->r0 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g0 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b0 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->r1 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g1 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b1 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->r2 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g2 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b2 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->vert0 = *(u16 *) ((u8 *) arg0 + 0xA);
        arg1->vert1 = *(u16 *) ((u8 *) arg0 + 0xE);
        arg1->vert2 = *(u16 *) ((u8 *) arg0 + 0x12);
        arg1->norm0 = *(u16 *) ((u8 *) arg0 + 0x8);
        arg1->norm1 = *(u16 *) ((u8 *) arg0 + 0xC);
        arg1->norm2 = *(u16 *) ((u8 *) arg0 + 0x10);
        return 0x14;
    case 0x24020507:
    case 0x24000507:
        if (GetGraphDebug() == 2) {
            printf(RO_STR_0000180C);
        }
        arg1->tpage = *(u16 *) ((u8 *) arg0 + 0xA);
        arg1->clut = *(u16 *) ((u8 *) arg0 + 0x6);
        arg1->u0 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->v0 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->u1 = *(u8 *) ((u8 *) arg0 + 0x8);
        arg1->v1 = *(u8 *) ((u8 *) arg0 + 0x9);
        arg1->u2 = *(u8 *) ((u8 *) arg0 + 0xC);
        arg1->v2 = *(u8 *) ((u8 *) arg0 + 0xD);
        arg1->vert0 = *(u16 *) ((u8 *) arg0 + 0x12);
        arg1->vert1 = *(u16 *) ((u8 *) arg0 + 0x14);
        arg1->vert2 = *(u16 *) ((u8 *) arg0 + 0x16);
        arg1->norm0 = *(u16 *) ((u8 *) arg0 + 0x10);
        arg1->norm1 = *(u16 *) ((u8 *) arg0 + 0x10);
        arg1->norm2 = *(u16 *) ((u8 *) arg0 + 0x10);
        return 0x18;
    case 0x34020609:
    case 0x34000609:
        if (GetGraphDebug() == 2) {
            printf(RO_STR_00001814);
        }
        arg1->tpage = *(u16 *) ((u8 *) arg0 + 0xA);
        arg1->clut = *(u16 *) ((u8 *) arg0 + 0x6);
        arg1->u0 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->v0 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->u1 = *(u8 *) ((u8 *) arg0 + 0x8);
        arg1->v1 = *(u8 *) ((u8 *) arg0 + 0x9);
        arg1->u2 = *(u8 *) ((u8 *) arg0 + 0xC);
        arg1->v2 = *(u8 *) ((u8 *) arg0 + 0xD);
        arg1->vert0 = *(u16 *) ((u8 *) arg0 + 0x12);
        arg1->vert1 = *(u16 *) ((u8 *) arg0 + 0x16);
        arg1->vert2 = *(u16 *) ((u8 *) arg0 + 0x1A);
        arg1->norm0 = *(u16 *) ((u8 *) arg0 + 0x10);
        arg1->norm1 = *(u16 *) ((u8 *) arg0 + 0x14);
        arg1->norm2 = *(u16 *) ((u8 *) arg0 + 0x18);
        return 0x1C;
    case 0x21030304:
    case 0x21010304:
        if (GetGraphDebug() == 2) {
            printf(RO_STR_0000181C);
        }
        arg1->r0 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g0 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b0 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->r1 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g1 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b1 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->r2 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g2 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b2 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->vert0 = *(u16 *) ((u8 *) arg0 + 0x8);
        arg1->vert1 = *(u16 *) ((u8 *) arg0 + 0xA);
        arg1->vert2 = *(u16 *) ((u8 *) arg0 + 0xC);
        return 0x10;
    case 0x31030506:
    case 0x31010506:
        if (GetGraphDebug() == 2) {
            printf(RO_STR_00001820);
        }
        arg1->r0 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g0 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b0 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->r1 = *(u8 *) ((u8 *) arg0 + 0x8);
        arg1->g1 = *(u8 *) ((u8 *) arg0 + 0x9);
        arg1->b1 = *(u8 *) ((u8 *) arg0 + 0xA);
        arg1->r2 = *(u8 *) ((u8 *) arg0 + 0xC);
        arg1->g2 = *(u8 *) ((u8 *) arg0 + 0xD);
        arg1->b2 = *(u8 *) ((u8 *) arg0 + 0xE);
        arg1->vert0 = *(u16 *) ((u8 *) arg0 + 0x10);
        arg1->vert1 = *(u16 *) ((u8 *) arg0 + 0x12);
        arg1->vert2 = *(u16 *) ((u8 *) arg0 + 0x14);
        return 0x18;
    case 0x25030607:
    case 0x25010607:
        if (GetGraphDebug() == 2) {
            printf(RO_STR_00001824);
        }
        arg1->tpage = *(u16 *) ((u8 *) arg0 + 0xA);
        arg1->clut = *(u16 *) ((u8 *) arg0 + 0x6);
        arg1->u0 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->v0 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->u1 = *(u8 *) ((u8 *) arg0 + 0x8);
        arg1->v1 = *(u8 *) ((u8 *) arg0 + 0x9);
        arg1->u2 = *(u8 *) ((u8 *) arg0 + 0xC);
        arg1->v2 = *(u8 *) ((u8 *) arg0 + 0xD);
        arg1->r0 = *(u8 *) ((u8 *) arg0 + 0x10);
        arg1->g0 = *(u8 *) ((u8 *) arg0 + 0x11);
        arg1->b0 = *(u8 *) ((u8 *) arg0 + 0x12);
        arg1->r1 = *(u8 *) ((u8 *) arg0 + 0x10);
        arg1->g1 = *(u8 *) ((u8 *) arg0 + 0x11);
        arg1->b1 = *(u8 *) ((u8 *) arg0 + 0x12);
        arg1->r2 = *(u8 *) ((u8 *) arg0 + 0x10);
        arg1->g2 = *(u8 *) ((u8 *) arg0 + 0x11);
        arg1->b2 = *(u8 *) ((u8 *) arg0 + 0x12);
        arg1->vert0 = *(u16 *) ((u8 *) arg0 + 0x14);
        arg1->vert1 = *(u16 *) ((u8 *) arg0 + 0x16);
        arg1->vert2 = *(u16 *) ((u8 *) arg0 + 0x18);
        return 0x1C;
    case 0x35030809:
    case 0x35010809:
        if (GetGraphDebug() == 2) {
            printf(RO_STR_0000182C);
        }
        arg1->tpage = *(u16 *) ((u8 *) arg0 + 0xA);
        arg1->clut = *(u16 *) ((u8 *) arg0 + 0x6);
        arg1->u0 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->v0 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->u1 = *(u8 *) ((u8 *) arg0 + 0x8);
        arg1->v1 = *(u8 *) ((u8 *) arg0 + 0x9);
        arg1->u2 = *(u8 *) ((u8 *) arg0 + 0xC);
        arg1->v2 = *(u8 *) ((u8 *) arg0 + 0xD);
        arg1->vert0 = *(u16 *) ((u8 *) arg0 + 0x1C);
        arg1->vert1 = *(u16 *) ((u8 *) arg0 + 0x1E);
        arg1->vert2 = *(u16 *) ((u8 *) arg0 + 0x20);
        arg1->r0 = *(u8 *) ((u8 *) arg0 + 0x10);
        arg1->g0 = *(u8 *) ((u8 *) arg0 + 0x11);
        arg1->b0 = *(u8 *) ((u8 *) arg0 + 0x12);
        arg1->r1 = *(u8 *) ((u8 *) arg0 + 0x14);
        arg1->g1 = *(u8 *) ((u8 *) arg0 + 0x15);
        arg1->b1 = *(u8 *) ((u8 *) arg0 + 0x16);
        arg1->r2 = *(u8 *) ((u8 *) arg0 + 0x18);
        arg1->g2 = *(u8 *) ((u8 *) arg0 + 0x19);
        arg1->b2 = *(u8 *) ((u8 *) arg0 + 0x1A);
        return 0x24;
    case 0x28020405:
    case 0x28000405:
        if (GetGraphDebug() == 2) {
            printf(RO_STR_00001834);
        }
        arg1->r0 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g0 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b0 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->r1 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g1 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b1 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->r2 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g2 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b2 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->r3 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g3 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b3 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->vert0 = *(u16 *) ((u8 *) arg0 + 0xA);
        arg1->vert1 = *(u16 *) ((u8 *) arg0 + 0xC);
        arg1->vert2 = *(u16 *) ((u8 *) arg0 + 0xE);
        arg1->vert3 = *(u16 *) ((u8 *) arg0 + 0x10);
        arg1->norm0 = *(u16 *) ((u8 *) arg0 + 0x8);
        arg1->norm1 = *(u16 *) ((u8 *) arg0 + 0x8);
        arg1->norm2 = *(u16 *) ((u8 *) arg0 + 0x8);
        arg1->norm3 = *(u16 *) ((u8 *) arg0 + 0x8);
        return 0x14;
    case 0x38020508:
    case 0x38000508:
        if (GetGraphDebug() == 2) {
            printf(RO_STR_0000183C);
        }
        arg1->r0 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g0 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b0 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->r1 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g1 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b1 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->r2 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g2 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b2 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->r3 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g3 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b3 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->vert0 = *(u16 *) ((u8 *) arg0 + 0xA);
        arg1->vert1 = *(u16 *) ((u8 *) arg0 + 0xE);
        arg1->vert2 = *(u16 *) ((u8 *) arg0 + 0x12);
        arg1->vert3 = *(u16 *) ((u8 *) arg0 + 0x16);
        arg1->norm0 = *(u16 *) ((u8 *) arg0 + 0x8);
        arg1->norm1 = *(u16 *) ((u8 *) arg0 + 0xC);
        arg1->norm2 = *(u16 *) ((u8 *) arg0 + 0x10);
        arg1->norm3 = *(u16 *) ((u8 *) arg0 + 0x14);
        return 0x18;
    case 0x2C020709:
    case 0x2C000709:
        if (GetGraphDebug() == 2) {
            printf(RO_STR_00001844);
        }
        arg1->tpage = *(u16 *) ((u8 *) arg0 + 0xA);
        arg1->clut = *(u16 *) ((u8 *) arg0 + 0x6);
        arg1->u0 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->v0 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->u1 = *(u8 *) ((u8 *) arg0 + 0x8);
        arg1->v1 = *(u8 *) ((u8 *) arg0 + 0x9);
        arg1->u2 = *(u8 *) ((u8 *) arg0 + 0xC);
        arg1->v2 = *(u8 *) ((u8 *) arg0 + 0xD);
        arg1->u3 = *(u8 *) ((u8 *) arg0 + 0x10);
        arg1->v3 = *(u8 *) ((u8 *) arg0 + 0x11);
        arg1->vert0 = *(u16 *) ((u8 *) arg0 + 0x16);
        arg1->vert1 = *(u16 *) ((u8 *) arg0 + 0x18);
        arg1->vert2 = *(u16 *) ((u8 *) arg0 + 0x1A);
        arg1->vert3 = *(u16 *) ((u8 *) arg0 + 0x1C);
        arg1->norm0 = *(u16 *) ((u8 *) arg0 + 0x14);
        arg1->norm1 = *(u16 *) ((u8 *) arg0 + 0x14);
        arg1->norm2 = *(u16 *) ((u8 *) arg0 + 0x14);
        arg1->norm3 = *(u16 *) ((u8 *) arg0 + 0x14);
        return 0x20;
    case 0x3C02080C:
    case 0x3C00080C:
        if (GetGraphDebug() == 2) {
            printf(RO_STR_0000184C);
        }
        arg1->tpage = *(u16 *) ((u8 *) arg0 + 0xA);
        arg1->clut = *(u16 *) ((u8 *) arg0 + 0x6);
        arg1->u0 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->v0 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->u1 = *(u8 *) ((u8 *) arg0 + 0x8);
        arg1->v1 = *(u8 *) ((u8 *) arg0 + 0x9);
        arg1->u2 = *(u8 *) ((u8 *) arg0 + 0xC);
        arg1->v2 = *(u8 *) ((u8 *) arg0 + 0xD);
        arg1->u3 = *(u8 *) ((u8 *) arg0 + 0x10);
        arg1->v3 = *(u8 *) ((u8 *) arg0 + 0x11);
        arg1->vert0 = *(u16 *) ((u8 *) arg0 + 0x16);
        arg1->vert1 = *(u16 *) ((u8 *) arg0 + 0x1A);
        arg1->vert2 = *(u16 *) ((u8 *) arg0 + 0x1E);
        arg1->vert3 = *(u16 *) ((u8 *) arg0 + 0x22);
        arg1->norm0 = *(u16 *) ((u8 *) arg0 + 0x14);
        arg1->norm1 = *(u16 *) ((u8 *) arg0 + 0x18);
        arg1->norm2 = *(u16 *) ((u8 *) arg0 + 0x1C);
        arg1->norm3 = *(u16 *) ((u8 *) arg0 + 0x20);
        return 0x24;
    case 0x29030305:
    case 0x29010305:
        if (GetGraphDebug() == 2) {
            printf(RO_STR_00001854);
        }
        arg1->r0 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g0 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b0 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->r1 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g1 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b1 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->r2 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g2 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b2 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->r3 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g3 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b3 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->vert0 = *(u16 *) ((u8 *) arg0 + 0x8);
        arg1->vert1 = *(u16 *) ((u8 *) arg0 + 0xA);
        arg1->vert2 = *(u16 *) ((u8 *) arg0 + 0xC);
        arg1->vert3 = *(u16 *) ((u8 *) arg0 + 0xE);
        return 0x10;
    case 0x39030608:
    case 0x39010608:
        if (GetGraphDebug() == 2) {
            printf(RO_STR_00001858);
        }
        arg1->r0 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->g0 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->b0 = *(u8 *) ((u8 *) arg0 + 0x6);
        arg1->r1 = *(u8 *) ((u8 *) arg0 + 0x8);
        arg1->g1 = *(u8 *) ((u8 *) arg0 + 0x9);
        arg1->b1 = *(u8 *) ((u8 *) arg0 + 0xA);
        arg1->r2 = *(u8 *) ((u8 *) arg0 + 0xC);
        arg1->g2 = *(u8 *) ((u8 *) arg0 + 0xD);
        arg1->b2 = *(u8 *) ((u8 *) arg0 + 0xE);
        arg1->r3 = *(u8 *) ((u8 *) arg0 + 0x10);
        arg1->g3 = *(u8 *) ((u8 *) arg0 + 0x11);
        arg1->b3 = *(u8 *) ((u8 *) arg0 + 0x12);
        arg1->vert0 = *(u16 *) ((u8 *) arg0 + 0x14);
        arg1->vert1 = *(u16 *) ((u8 *) arg0 + 0x16);
        arg1->vert2 = *(u16 *) ((u8 *) arg0 + 0x18);
        arg1->vert3 = *(u16 *) ((u8 *) arg0 + 0x1A);
        return 0x1C;
    case 0x2D030709:
    case 0x2D010709:
        if (GetGraphDebug() == 2) {
            printf(RO_STR_0000185C);
        }
        arg1->tpage = *(u16 *) ((u8 *) arg0 + 0xA);
        arg1->clut = *(u16 *) ((u8 *) arg0 + 0x6);
        arg1->u0 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->v0 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->u1 = *(u8 *) ((u8 *) arg0 + 0x8);
        arg1->v1 = *(u8 *) ((u8 *) arg0 + 0x9);
        arg1->u2 = *(u8 *) ((u8 *) arg0 + 0xC);
        arg1->v2 = *(u8 *) ((u8 *) arg0 + 0xD);
        arg1->u3 = *(u8 *) ((u8 *) arg0 + 0x10);
        arg1->v3 = *(u8 *) ((u8 *) arg0 + 0x11);
        arg1->r0 = *(u8 *) ((u8 *) arg0 + 0x14);
        arg1->g0 = *(u8 *) ((u8 *) arg0 + 0x15);
        arg1->b0 = *(u8 *) ((u8 *) arg0 + 0x16);
        arg1->r1 = *(u8 *) ((u8 *) arg0 + 0x14);
        arg1->g1 = *(u8 *) ((u8 *) arg0 + 0x15);
        arg1->b1 = *(u8 *) ((u8 *) arg0 + 0x16);
        arg1->r2 = *(u8 *) ((u8 *) arg0 + 0x14);
        arg1->g2 = *(u8 *) ((u8 *) arg0 + 0x15);
        arg1->b2 = *(u8 *) ((u8 *) arg0 + 0x16);
        arg1->r3 = *(u8 *) ((u8 *) arg0 + 0x14);
        arg1->g3 = *(u8 *) ((u8 *) arg0 + 0x15);
        arg1->b3 = *(u8 *) ((u8 *) arg0 + 0x16);
        arg1->vert0 = *(u16 *) ((u8 *) arg0 + 0x18);
        arg1->vert1 = *(u16 *) ((u8 *) arg0 + 0x1A);
        arg1->vert2 = *(u16 *) ((u8 *) arg0 + 0x1C);
        arg1->vert3 = *(u16 *) ((u8 *) arg0 + 0x1E);
        return 0x20;
    case 0x3D010A0C:
    case 0x3D030A0C:
        if (GetGraphDebug() == 2) {
            printf(RO_STR_00001864);
        }
        arg1->tpage = *(u16 *) ((u8 *) arg0 + 0xA);
        arg1->clut = *(u16 *) ((u8 *) arg0 + 0x6);
        arg1->u0 = *(u8 *) ((u8 *) arg0 + 0x4);
        arg1->v0 = *(u8 *) ((u8 *) arg0 + 0x5);
        arg1->u1 = *(u8 *) ((u8 *) arg0 + 0x8);
        arg1->v1 = *(u8 *) ((u8 *) arg0 + 0x9);
        arg1->u2 = *(u8 *) ((u8 *) arg0 + 0xC);
        arg1->v2 = *(u8 *) ((u8 *) arg0 + 0xD);
        arg1->u3 = *(u8 *) ((u8 *) arg0 + 0x10);
        arg1->v3 = *(u8 *) ((u8 *) arg0 + 0x11);
        arg1->vert0 = *(u16 *) ((u8 *) arg0 + 0x24);
        arg1->vert1 = *(u16 *) ((u8 *) arg0 + 0x26);
        arg1->vert2 = *(u16 *) ((u8 *) arg0 + 0x28);
        arg1->vert3 = *(u16 *) ((u8 *) arg0 + 0x2A);
        arg1->r0 = *(u8 *) ((u8 *) arg0 + 0x14);
        arg1->g0 = *(u8 *) ((u8 *) arg0 + 0x15);
        arg1->b0 = *(u8 *) ((u8 *) arg0 + 0x16);
        arg1->r1 = *(u8 *) ((u8 *) arg0 + 0x18);
        arg1->g1 = *(u8 *) ((u8 *) arg0 + 0x19);
        arg1->b1 = *(u8 *) ((u8 *) arg0 + 0x1A);
        arg1->r2 = *(u8 *) ((u8 *) arg0 + 0x1C);
        arg1->g2 = *(u8 *) ((u8 *) arg0 + 0x1D);
        arg1->b2 = *(u8 *) ((u8 *) arg0 + 0x1E);
        arg1->r3 = *(u8 *) ((u8 *) arg0 + 0x20);
        arg1->g3 = *(u8 *) ((u8 *) arg0 + 0x21);
        arg1->b3 = *(u8 *) ((u8 *) arg0 + 0x22);
        return 0x2C;
    default:
        printf(RO_STR_0000186C, arg1->id & 0xFDFFFFFF);
        return -1;
    }
}
