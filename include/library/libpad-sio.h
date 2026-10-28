#ifndef LIBRARY_LIBPAD_SIO_H
#define LIBRARY_LIBPAD_SIO_H

#include "libpad-direct.h"
#include "libpad-enable-com.h"

/* PDRESRES .data+0x80 (D_00001F70) holds 0x1F801040. Original
 * _padInitSioMode accesses byte +0 and halfwords +4/+8/+A/+E;
 * _padIntPad and the reset/wait helpers share these SIO0 registers. */
typedef struct PadSioRegisters {
    volatile u8 data;
    u8 pad1[3];
    volatile u16 status;
    u16 pad6;
    volatile u16 mode;
    volatile u16 control;
    u16 padC;
    volatile u16 baud;
} PadSioRegisters;
extern PadSioRegisters *D_00001F70;

/* PDRESRES .data+0x7C holds 0x1F801070. _padIsVsync reads both
 * interrupt words; _padInitSioMode polls/acknowledges word 0 bit 0x80. */
extern volatile u32 *D_00001F6C;

/* PDRESRES word objects at .data+0x48/+0x4C/+0x78; the per-channel
 * result words at +0x60/+0x64 are initialized to -1. */
extern int _padSioChan;
extern int _padSioState;
extern int _padCalledIntPad;
extern int _padFixResult[2];

/* Original same-member calls: Init consumes a0 and returns the tested
 * status; func_000005AC consumes only a0 and its result is unused. */
int _padInitSioMode(PadInfo2 *info);
/* PDRESRES local helper: absent from the original external symbol records;
 * its same-TU caller _padIntPad supplies the per-port record. */
static void func_000005AC(PadInfo2 *info);

/* PDRESRES .data+0x90: five relocated state-handler pointers. The dispatch
 * preserves incoming a0 (PadInfo2 *) and tests each handler's v0 result. */
extern int (*D_00001F80[5])(PadInfo2 *);

/* Original reset/wait helpers: Set stores incoming a0; Chk and Clr
 * read no incoming arguments and return tested status values. */
void _padSetRC2wait(int count);
int _padChkRC2wait(void);
int _padClrIntSio0(void);
void _padWaitRXready(void);

/* PDRESRES .bss+0x4/+0x8/+0xC timer state. _padSioRW records
 * counter/mode snapshots at 0x1F801120/0x1F801124 and the timeout;
 * _padSioRW2 compares signed elapsed counts with that timeout. */
extern s32 B_00001FA4;
extern s32 B_00001FA8;
extern u32 B_00001FAC;

/* The exchanges write the second argument's low byte to SIO data,
 * returning the received byte or a negative timeout status. _padSioRW
 * also tests the incoming argument's sign for its initial exchange. */
int _padSioRW(PadInfo2 *info, int data);
int _padSioRW2(PadInfo2 *pad, int data);

#endif
