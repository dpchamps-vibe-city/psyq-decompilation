#ifndef LIBRARY_LIBMCX_RESI_H
#define LIBRARY_LIBMCX_RESI_H

#include "libmcx_transfer.h"

/* MCXRESI exported data labels at .data+0x30, +0x34 and +0x38. */
extern int _mcxStat;
extern int _mcxCmdSeq;
extern int _mcxPort;
/* _mcxStepSio reloads the command number in adjacent tests without a call
 * or store between them (listing .text+0x434 and .text+0x448). */
extern volatile int _mcxFuncNo;
/* MCXRESI byte-buffer stores and the installed command callback contracts. */
extern unsigned char _mcxTxBuf[];
extern unsigned char _mcxRxBuf[];
extern int (*_mcxFuncGetTx)(void);
extern int (*_mcxFuncApplyRx)(int);
/* MCXRESI .data+0x4C holds SIO0 0x1F801040; reads are byte at0 and
 * volatile halfword at4. This local label is distinct from other members. */
extern volatile unsigned char *D_00000574;

/* MCXMAIN originals read only a0; InitSioMode returns a status word,
 * and SioRW returns the received byte or a negative status. */
int _mcxInitSioMode(int port);
int _mcxSioRW(int data);

#endif
