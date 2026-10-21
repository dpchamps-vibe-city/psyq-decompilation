#include "common.h"
#include <sys/types.h>
#include <libcd.h>
#include <libetc.h>
#include <stdio.h>

typedef struct {
    u32 unk0;
    u32 unk4;
    u_long *unk8;
    u32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    CdlCB unk28;
    CdlCB unk2C;
    void (*unk30)();
    u8 *unk34;
} CdReadState;

typedef struct {
    u_long *unk0;
    u32 unk4;
    s32 unk8;
} CdReadBuf;

extern int func_000003F0(s32 arg0) __asm__("$Lfunc_000003F0");
extern CdReadState D_00000A68 __asm__("$LD_00000A68");
extern CdReadBuf D_00000A70 __asm__("$LD_00000A70");
extern s32 CD_read_dma_mode;
extern s32 D_00000A88 __asm__("$LD_00000A88");
extern void (*CD_cbread)(u8, u8 *);
extern char CdRead_sector_error[] __asm__("$LRO_STR_00000A18");

/* Keep the callback's link name in this TU part so regenerated assembly
 * fragments use the same local symbol as the compiled callback. */
static void func_00000078(void) __asm__("$Lfunc_00000078");
static void func_00000320(void) __asm__("$LT_00000320");

#include "cdr1_private_head.h"

static void func_000000AC(u8 arg0, u8 *arg1) {
    u_long sp10[4];

    {
        volatile CdReadState *cd;

    cd = (volatile CdReadState *)&D_00000A68;
    cd->unk34 = arg1;
    if (arg0 == 1) {
        if (cd->unk14 > 0) {
            if (cd->unk10 == 0x200) {
                s32 *sect;
                volatile CdReadState *st;

                if (CD_read_dma_mode & 1) {
                    CdDataCallback(0);
                    CdGetSector2(sp10, 3);
                    CdDataSync(0);
                    CdDataCallback(func_00000320);
                } else {
                    CdGetSector(sp10, 3);
                }
                sect = &D_00000A88;
                if (CdPosToInt((CdlLOC *)sp10) != *sect) {
                    puts(CdRead_sector_error);
                    st = (volatile CdReadState *)((u8 *)sect - 0x20);
                    st->unk14 = -1;
                }
            }
            if (CD_read_dma_mode & 1) {
                CdGetSector2(D_00000A70.unk0, D_00000A70.unk8);
            } else {
                volatile CdReadState *st;

                CdGetSector(D_00000A70.unk0, D_00000A70.unk8);
                st = (volatile CdReadState *)((u8 *)&D_00000A70 - 8);
                st->unk8 =
                    (u_long *)((u8 *)D_00000A70.unk0 + D_00000A70.unk8 * 4);
                st->unk14 -= 1;
                st->unk20 += 1;
            }
        }
    } else {
        cd->unk14 = -1;
    }
    }

    {
        volatile CdReadState *cd;

    cd = (volatile CdReadState *)&D_00000A68;
    cd->unk18 = VSync(-1);
    if (cd->unk14 < 0) {
        func_000003F0(1);
    }
    if (VSync(-1) > cd->unk1C + 0x4B0) {
        cd->unk14 = -1;
    }
    if (cd->unk14 == 0 || VSync(-1) > cd->unk1C + 0x4B0) {
        CdReadyCallback(cd->unk2C);
        if (CD_read_dma_mode & 1) {
            CdDataCallback(cd->unk30);
        }
        CdSyncCallback((CdlCB)func_00000078);
        CdControlF(9, 0);
        cd->unk24 = 1;
        if (CD_cbread != 0) {
            CD_cbread((cd->unk14 == 0) ? 2 : 5, arg1);
        }
    }
    }
}

#include "cdr1_private_tail.h"
