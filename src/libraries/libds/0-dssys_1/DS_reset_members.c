#include "common.h"

typedef unsigned char u_char;

typedef struct {
	u_char minute;
	u_char second;
	u_char sector;
	u_char track;
} DslLOC;

DslLOC *DsIntToPos(int i, DslLOC *p);

typedef struct {
	s32 active;
	u8 command;
	u8 param[4];
	u8 pad[3];
} DsCommand;

typedef struct {
	s32 status;
	u8 result[8];
} DsResult;

typedef struct {
	u8 status;
	u8 pad0[3];
	s32 unk4;
	s32 unk8;
	s32 unkC;
	s32 unk10;
	u8 lastcom;
	u8 lastmode;
	DslLOC lastpos;
	u8 lastseek;
	u8 lastread;
	u8 unk1C;
	u8 unk1D;
	u8 unk1E;
	u8 unk1F;
	s32 unk20;
	s32 shell_open;
	s32 unk28;
	s32 unk2C;
	s32 unk30;
	s32 unk34;
	u8 unk38;
	u8 unk39;
} DsSystem;

extern volatile s32 LD_00001240 __asm__("D_00001240");
extern DsResult D_0000124C;
extern DsSystem LD_00001258 __asm__("D_00001258");

#define SYS ((DsCommand *) &LD_00001240)

void DS_reset_members(void) {
    s32 i;

    u8 *p;
    u8 *q;

    SYS->active = 0;
    SYS->command = 0;
    i = 3;
    p = (u8 *) &LD_00001240 + 8;
    for (; i >= 0; i--) {
        *p-- = 0;
    }
    D_0000124C.status = 0;
    i = 7;
    q = (u8 *) &D_0000124C + 0xB;
    for (; i >= 0; i--) {
        *q-- = 0;
    }
    LD_00001258.status = 0;
    LD_00001258.unk4 = 0;
    LD_00001258.unk8 = 2;
    LD_00001258.unkC = 0xE;
    LD_00001258.unk10 = 0x15;
    LD_00001258.lastcom = 0;
    LD_00001258.lastmode = 0;
    DsIntToPos(0, &LD_00001258.lastpos);
    LD_00001258.lastseek = 0;
    LD_00001258.lastread = 0;
    LD_00001258.unk1C = 0;
    LD_00001258.unk1D = 0;
    LD_00001258.unk1E = 0;
    LD_00001258.unk1F = 0;
    LD_00001258.unk20 = 0;
    LD_00001258.shell_open = 1;
    LD_00001258.unk28 = 0;
    LD_00001258.unk30 = 0;
    LD_00001258.unk2C = 0;
    LD_00001258.unk34 = 0;
    LD_00001258.unk38 = 0;
    LD_00001258.unk39 = 0;
}
