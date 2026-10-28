#ifndef LIBRARY_LIBMCX_COMMAND_SETUP_H
#define LIBRARY_LIBMCX_COMMAND_SETUP_H

#include "libmcx_transfer.h"

/* MCXRESI _mcxStepSio reloads the command number in adjacent tests at
 * .text+0x434/+0x448 without a call or store (see libmcx_resi.h).
 * MCXCMD7's setup stores require this volatile view too: it preserves the
 * return-one guard delay slot and reproduces the complete original OBJ. */
extern volatile int _mcxFuncNo;
/* Original command setters write these as words and install callbacks. */
extern int _mcxStat;
extern int _mcxParam;
extern long *_mcxPtrCmdBuf0;
extern long *_mcxPtrCmdBuf1;
extern int (*_mcxFuncGetTx)(void);
extern int (*_mcxFuncApplyRx)(int);

/* MCXMAIN stores incoming a0 to _mcxPort; MCXCMD27 reads area and address. */
int _mcxChkRsrv(int port);
int chkMemArea(int area, unsigned int address);
/* MCXCMD8 and MCXCMD15 command callback entry contracts. */
int _mcxTxSetMem(void);
int _mcxRxSetMem(int value);
int _mcxTxReadDev(void);
int _mcxRxReadDev(int value);

#endif
