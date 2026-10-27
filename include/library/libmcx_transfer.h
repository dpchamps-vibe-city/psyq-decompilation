#ifndef LIBRARY_LIBMCX_TRANSFER_H
#define LIBRARY_LIBMCX_TRANSFER_H

/* MCXCMD6 original word loads/stores and byte-indexed destination. */
extern int _mcxDataLen;
extern unsigned char *_mcxPtrBuff;
extern int _mcxRestSize;
extern int _mcxRxLen;
extern int _mcxTxLen;
/* MCXCOM4 .text+0x3BC reads this checksum with lbu. */
extern unsigned char _mcxSum;
/* MCXCMD13 .bss+0x170: 16-byte command data buffer filled by McxSetTime. */
extern unsigned char B_00000170[];
/* MCXCMD12 .data+0x370 accesses _mcxFlag as a word; MCXCMD13 clears it here. */
extern int _mcxFlag;

/* FASTDRVR entry preserves all four argument registers; MCXCMD6 .text+0x180
 * passes direction, buffer, byte count and checksum address. Return unused. */
void _mcxStartFastDsr(int direction, unsigned char *buffer, int count,
                      unsigned char *checksum);

#endif
