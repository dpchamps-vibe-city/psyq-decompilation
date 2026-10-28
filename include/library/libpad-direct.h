#ifndef LIBRARY_LIBPAD_DIRECT_H
#define LIBRARY_LIBPAD_DIRECT_H

#include "libpad-internal.h"

/* PDDIRRES .bss contains two 0xF0-byte port records, followed by
 * independent 0x48-byte byte-buffer pools at the original labels. */
extern PadInfo2 B_00000AC0[2];
extern u8 B_00000CA0[0x48];
extern u8 B_00000CE8[0x48];

/* Installed PDDIRRES helpers read only these incoming arguments.
 * PDRESRES calls NextPort with its integer engine state; the remaining
 * callbacks operate on the current PadInfo2 record. Existing shared
 * declarations cover ClrInfo, Port2Info and ChkEng. */
extern void (*_padFuncNextPort)(int);
extern u8 (*_padFuncGetTxd)(PadInfo2 *);
extern void (*_padFuncCurrLimit)(PadInfo2 *);
extern void (*_padFuncClrCmdNo)(PadInfo2 *);
extern int (*_padFuncSendAuto)(PadInfo2 *);
extern void (*_padFuncRecvAuto)(PadInfo2 *);

#endif
