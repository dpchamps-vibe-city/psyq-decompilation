#ifndef LIBRARY_LIBPAD_INTERNAL_H
#define LIBRARY_LIBPAD_INTERNAL_H

#include "common.h"

/* Partial view of the libpad per-port status record returned by the
 * _padFuncPort2Info callback. Only the fields this project's original code
 * witnesses are named; offsets 0x30..0x33 are not exercised here.
 * Original-code evidence (whole-library word census):
 *   +0x28  pointer, stored with `sw` and reloaded with `lw`
 *          (libpad_0 PadSetAct, libpad_8 _padSetGunPort, libpad_11/17/18)
 *   +0x34  byte, stored with `sb` and reloaded with `lbu`
 *          (same sites; libpad_17 func_000002CC reads it as a loop bound)
 */
typedef struct {
    u8 pad0[0x28];
    u8 *actTable;   /* +0x28: active actuator table */
    u8 pad2C[8];
    u8 actSize;     /* +0x34: active actuator table length */
} PadInfo2;

/* Slot installed by _padInitDirPort/_padInitMtapPort with func_00000604 /
 * func_000006E4, both of which read only $a0 (`andi $a0,0xF0`) and return a
 * PadInfo2 pointer, so the callback takes one integer port argument. */
typedef PadInfo2 *(*PadGetPort2InfoFunc)(int port);

extern PadGetPort2InfoFunc _padFuncPort2Info;

#endif
