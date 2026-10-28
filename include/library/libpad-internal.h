#ifndef LIBRARY_LIBPAD_INTERNAL_H
#define LIBRARY_LIBPAD_INTERNAL_H

#include "common.h"

/* Partial per-port record. PDCMD2 PadSetActAlign stores prepare/apply
 * callbacks at +0x14/+0x18, its SDK byte-buffer argument at +0x20 and
 * a command state byte at +0x46. Its Tx helper passes +0x20 to
 * _padSetCmd; that callee stores the pointer at +0x2C. */
typedef struct PadInfo2 PadInfo2;
struct PadInfo2 {
    u8 pad0[0x14];
    void (*prepareCommand)(PadInfo2 *);
    int (*applyResponse)(PadInfo2 *);
    u8 pad1C[4];
    u8 *commandTable;
    u8 pad24[4];
    /* PDCMD1 PadSetAct, PDRESRES and PDDIR/PDMTAP witness +0x28
     * as a pointer (sw/lw), and +0x34 as a byte (sb/lbu). */
    u8 *actTable;
    u8 pad2C[8];
    u8 actSize;
    u8 pad35[0x11];
    u8 commandState;
};

/* Installed targets PDDIR func_00000604 / PDMTAP func_000006E4
 * read only the integer port in a0 and return the per-port pointer. */
typedef PadInfo2 *(*PadGetPort2InfoFunc)(int port);
extern PadGetPort2InfoFunc _padFuncPort2Info;

/* PDDIR func_00000A80 / PDMTAP func_000010F8 consume a0 as the
 * per-port record and return a Boolean engine-busy result in v0. */
extern int (*_padFuncChkEng)(PadInfo2 *);

/* PDRESRES _padSetCmd stores a1/a3 as bytes at +0x37/+0x36 and
 * a2 as a word at +0x2C; PDCMD2 supplies its byte-buffer pointer. */
void _padSetCmd(PadInfo2 *, int command, unsigned char *data, int length);

#endif
