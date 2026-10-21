/* Original TU: library-input/psyq/LIB/Libcd.lib[44] CDR_1.OBJ
 * sha256: 35f052d672187ce1f56fb2bb54ec0919e31826da53c06ea0845e91356b699844
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: func_000000AC, func_000003F0, CdReadBreak, CdRead, CdReadSync
 */
#include "common.h"
#include "include_asm.h"
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

static int func_000003F0(s32 arg0);
extern volatile CdReadState D_00000A68;
extern CdReadBuf D_00000A70;
extern s32 CD_read_dma_mode;
extern s32 D_00000A88;
extern void (*CD_cbread)(u8, u8 *);
extern char RO_STR_00000A18[];

static void func_00000078(void);
static void func_00000320(void);
