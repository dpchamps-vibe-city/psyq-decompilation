#ifndef LIBRARY_LIBMCX_COMMAND_BYTES_H
#define LIBRARY_LIBMCX_COMMAND_BYTES_H

/* MCXCMD8 _mcxTxSetMem reloads the command sequence in its default arm
 * without an intervening store or call. Keep its volatile access contract
 * separate from the nonvolatile declarations used by other original TUs. */
extern volatile int _mcxCmdSeq;
/* MCXCMD7 stores one word; MCXCMD8 reads its four individual bytes. */
extern int _mcxParam;

#endif
