#ifndef LIBRARY_LIBPAD_COM_STOP_H
#define LIBRARY_LIBPAD_COM_STOP_H

#include <libapi.h>
#include <libpad.h>

/* PDRESRES owns this interrupt record at .data+0x68; PDMAIINI only
 * passes its address to the kernel, so leave the layout opaque. */
struct PadInterruptRecord;
extern struct PadInterruptRecord _padVsyncParam;

/* Independently matched LIBAPI PAD callers establish priority/record
 * arguments. PDMAIINI PadStopCom calls ChangeClearRCnt(3,1), while
 * PadStartCom and MCXINIT independently call (3,0). */
int SysDeqIntRP(int priority, void *record);
int ChangeClearRCnt(int counter, int enabled);

#endif
