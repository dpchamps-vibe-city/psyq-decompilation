#ifndef LIBRARY_LIBMCX_INTERNAL_H
#define LIBRARY_LIBMCX_INTERNAL_H

/* MCXCMD1 original stores and word accesses; McxGetApl's buffer type is
 * independently declared in the vendored libmcx.h SDK header. */
extern int _mcxParam;
extern int _mcxFuncNo;
extern int _mcxStat;
extern long *_mcxPtrCmdBuf0;
extern int (*_mcxFuncGetTx)(void);
extern int (*_mcxFuncApplyRx)(int);
extern int _mcxCmdSeq;

/* Original _mcxChkRsrv stores incoming $a0 to _mcxPort at .text+0x2E0. */
int _mcxChkRsrv(int port);

/* MCXCMD12 command callbacks; MCXCMD13 and the other command setters store
 * these in _mcxFuncGetTx / _mcxFuncApplyRx. */
int _mcxTxWriteDev(void);
int _mcxRxWriteDev(int value);

#endif
