#ifndef LIBRARY_LIBPAD_INTERNAL_H
#define LIBRARY_LIBPAD_INTERNAL_H

#include "common.h"

/* Partial per-port record. PDCMD2 PadSetActAlign stores prepare/apply
 * callbacks at +0x14/+0x18, its SDK byte-buffer argument at +0x20 and
 * a command state byte at +0x46. Its Tx helper passes +0x20 to
 * _padSetCmd; that callee stores the pointer at +0x2C. */
typedef struct PadInfo2 PadInfo2;
struct PadInfo2 {
    /* PDENT3 PadInfoMode's InfoModeIdTable reads halfword entries
     * through the pointer at +0. */
    u16 *idTable;
    /* PDCMD2 Rx reads this pointer at +4 and byte +2 of each
     * five-byte entry as a per-type limit. */
    u8 *actAlignData;
    u8 pad08[4];
    /* PDGUNRES _padSetGunPort dereferences +0xC as the mtap child-record
     * array (stride 0xF0, four entries) and adds row offsets to it. */
    PadInfo2 *child;
    /* PDENT2 PadGetState compares this pointer against the record itself
     * before it reads the +0x39 command byte. */
    PadInfo2 *root;
    void (*prepareCommand)(PadInfo2 *);
    int (*applyResponse)(PadInfo2 *);
    u8 pad1C[4];
    u8 *commandTable;
    u8 pad24[4];
    /* PDCMD1 PadSetAct, PDRESRES and PDDIR/PDMTAP witness +0x28
     * as a pointer (sw/lw), and +0x34 as a byte (sb/lbu). */
    u8 *actTable;
    u8 pad2C[4];
    /* PDENT2 PadGetState reads byte 0 of this pointer; PDRESRES
     * func_00000734 builds the command frame in the buffer it addresses. */
    u8 *commandBuffer;
    u8 actSize;
    u8 pad35[2];
    /* Command handshake bytes. PDENT2 PadGetState treats any non-zero value
     * as busy; PDRESRES moves +0x37 into +0x38 and +0x38 into +0x39. */
    u8 requestCommand;
    u8 currentCommand;
    u8 previousCommand;
    u8 pad3A[0xC];
    u8 commandState;
    /* PDCMD3 PadSetMainMode stores request/lock/equality bytes at
     * +0x51/+0x52/+0x53 and compares with the byte at +0xE4. */
    u8 pad47[2];
    /* PDENT2 PadGetState returns and switches on this byte. */
    u8 state;
    u8 pad4A[2];
    /* PDENT3 PadInfoMode selector 100 returns the word at +0x4C. */
    s32 unk4C;
    u8 pad50;
    u8 mode;
    u8 lock;
    u8 modeEqual;
    u8 pad54[9];
    /* PDCMD2 Rx writes six command-table response bytes +0x5D..0x62
     * and reads the number of types at +0xE9. Unnamed bytes remain opaque. */
    u8 actAlignResponse[6];
    u8 pad63[0x80];
    /* PDENT3 PadInfoMode bounds InfoModeIdTable with byte +0xE3. */
    u8 idCount;
    u8 prevMode;
    u8 padE5;
    /* PDENT3 PadInfoMode's InfoModeCurExID reads halfword +0xE6. */
    u16 exId;
    /* PDENT1 PadChkMtap indexes _padInfoDir with stride 0xF0 and
     * reads this byte at +0xE8; PDDIR/PDMTAP agree on the stride. */
    u8 mtapType;
    u8 actAlignCount;
    u8 padEA[6];
};

/* PDENT1 loads a pointer to the record array and tests the word mode. */
extern PadInfo2 *_padInfoDir;
extern int _padModeMtap;

/* Installed targets PDDIR func_00000604 / PDMTAP func_000006E4
 * read only the integer port in a0 and return the per-port pointer. */
typedef PadInfo2 *(*PadGetPort2InfoFunc)(int port);
extern PadGetPort2InfoFunc _padFuncPort2Info;

/* PDDIR func_00000A80 / PDMTAP func_000010F8 consume a0 as the
 * per-port record and return a Boolean engine-busy result in v0. */
extern int (*_padFuncChkEng)(PadInfo2 *);

/* PDDIR/PDMTAP init install the record-clearing callback; PadEnableCom
 * and PDCMD3 Rx call it with the per-port record in a0 and ignore its
 * result. The callback is loaded from this pointer object before jalr. */
extern void (*_padFuncClrInfo)(PadInfo2 *);

/* PDGUN .data: saved gun port records, their original command buffers and
 * the per-port command length. PDGUN/_padSetGunPort write the length back as
 * a word (sw) while a reader that only needs the +0x34 byte field narrows the
 * load to lbu, so the element is a word and the stride is 4. */
extern PadInfo2 *_padGunSavePadPtr[2];
extern u8 *_padGunSaveTxBuf[2];
extern u32 _padGunSaveTxLen[2];

/* PDGN1INI installs the no-argument PDGUN callbacks; PDGN1EXI clears
 * their pointer objects along with the run flag. */
extern s32 _padGunExec;
extern void (*_padFuncIntGun)(void);
extern void (*_padFuncSetGunPort)(void);
extern void (*_padFuncGetGunPos)(void);

/* PDHOKRES: gun hook called with no arguments and no result. */
void _padGunExitHook(void);

/* PDRESRES _padSetCmd stores a1/a3 as bytes at +0x37/+0x36 and
 * a2 as a word at +0x2C; PDCMD2 supplies its byte-buffer pointer. */
void _padSetCmd(PadInfo2 *, int command, unsigned char *data, int length);

/* PDGUNRES _padSetGunPort reads/writes the three port-state bytes at
 * 0x568..0x56A. The original target references 0x568 and 0x569 through
 * two independent HI/LO relocation pairs (data+0x28 and data+0x29), i.e.
 * they are separate objects, not elements of one array. Declaring them as
 * separate byte objects is what restores that code shape; a single
 * D_00000568[4] makes the compiler share one base and emits base+1.
 * D_00000568 and D_0000056A must be DEFINED at those addresses by the
 * member data definition (see DATA_SYMBOL_REQUEST.md in the worker dir). */
extern u8 D_00000568;
extern u8 D_00000569;
extern u8 D_0000056A;

#endif
