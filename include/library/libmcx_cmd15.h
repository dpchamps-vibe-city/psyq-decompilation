#ifndef LIBRARY_LIBMCX_CMD15_H
#define LIBRARY_LIBMCX_CMD15_H

#include "libmcx_command_bytes.h"
#include "libmcx_transfer.h"

/* MCXCMD15's receive callback uses the volatile sequence contract:
 * preserving the sequence update across RC2 wait setup reproduces the
 * original call-delay store. Other original TUs retain their own views. */
extern long *_mcxPtrCmdBuf0;
extern int (*_mcxFuncGetTx)(void);
extern int _mcxPass;
extern unsigned char _mcxRxBuf[];
extern unsigned char _mcxTxBuf[];

/* MCXCMD15 .data+0x570 = SIO0 (0x1F801040), +0x574 = I_STAT
 * (0x1F801070); original accesses are volatile byte/halfword and word. */
extern volatile unsigned char *D_00000570;
extern volatile unsigned int *D_00000574;

/* MCXMAIN originals: RC2 setup reads a0; wait check returns a status;
 * SIO transfer reads the outgoing byte in a0 and returns a status. */
int _mcxChkRC2wait(void);
void _mcxSetRC2wait(int command);
int _mcxSioRW(int data);

#endif
