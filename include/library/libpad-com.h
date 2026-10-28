#ifndef LIBRARY_LIBPAD_COM_H
#define LIBRARY_LIBPAD_COM_H

#include "libpad-internal.h"
#include <libapi.h>
#include <libpad.h>

/* PDRESRES owns the interrupt record at .data+0x68; PDMAIINI only
 * passes its address to the kernel. Keep the unaccessed layout opaque. */
struct PadInterruptRecord;
extern struct PadInterruptRecord _padVsyncParam;

/* PDRESRES owns a word run flag and the two signed-word rest counters
 * (.comm _padRestPeriod,8; _padIntPad increments/tests offsets 0 and 4). */
extern int _padIntExec;
extern int _padRestPeriod[2];

/* PDMAIINI .data+0 contains 0x1F801070. PadStartCom accesses its
 * status and mask words at offsets 0 and 4. */
extern volatile u32 *D_00000180;

/* Independently matched LIBAPI PAD callers establish the kernel's
 * priority/record arguments. MCXINIT independently calls (3,0). */
int SysDeqIntRP(int priority, void *record);
int SysEnqIntRP(int priority, void *record);
int ChangeClearRCnt(int counter, int enabled);

#endif
