#ifndef LIBRARY_LIBMCX_INIT_H
#define LIBRARY_LIBMCX_INIT_H

/* MCXRESI _mcxTblCardEnt is four words: next link, handler, readiness
 * callback and reserved word. MCXINIT's private enqueue walks offset0. */
typedef struct McxInterruptRecord {
    struct McxInterruptRecord *next;
    int (*handler)(void);
    int (*ready)(void);
    unsigned int reserved;
} McxInterruptRecord;

extern McxInterruptRecord _mcxTblCardEnt;
/* MCXINIT .data+0 holds I_STAT 0x1F801070; McxStartCom accesses its
 * acknowledgement and mask words at offsets0 and4. */
extern volatile unsigned int *D_00000180;

/* MCXINIT private enqueue loads a queue-table pointer through data+4
 * (D_00000184, initialized to 0x100), indexing eight-byte entries. */
typedef struct McxInterruptQueue {
    McxInterruptRecord *head;
    unsigned int reserved;
} McxInterruptQueue;
extern McxInterruptQueue **D_00000184;

/* SysDeqIntRP agrees with the independently matched LIBAPI PAD callers.
 * MCXINIT sets both argument registers for ChangeClearRCnt (3,0). */
int SysDeqIntRP(int priority, void *record);
int ChangeClearRCnt(int counter, int enabled);
/* MCXINIT McxStopCom calls this without arguments and ignores its result;
 * MCXDSR .text+0x164 reads no incoming argument registers. */
void _mcxStopFastDsr(void);

#endif
