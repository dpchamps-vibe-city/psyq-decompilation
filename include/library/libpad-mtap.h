#ifndef LIBRARY_LIBPAD_MTAP_H
#define LIBRARY_LIBPAD_MTAP_H

#include "libpad-internal.h"

/* PDMTAPRES member data: root records (0x1E0 bytes), eight child records
 * (0x780 bytes), and two 0x48-byte frame buffers. Keep the extracted
 * private storage labels; _padInitMtapPort supplies the record views. */
extern u8 B_000011C0[];
extern u8 B_000013A0[];
extern u8 B_00001B20[];
extern u8 B_00001B68[];

/* PDTAPINI PadInitMtap: two per-port last-result words, cleared at init. */
extern int _mtapLastResult[2];

/* PDTAPRES member 18 installs the multitap port driver callbacks;
 * PadInitMtap calls it with no arguments and ignores any result. */
void _padInitMtapPort(void);

/* PDRESRES .data+8/+0x10/+0x14/+0x20/+0x28/+0x2C callback objects.
 * PDRESRES _padIntPad supplies an integer result to NextPort (0x1F0).
 * _padChkRC2wait consumes SendAuto's word result (0x1620..0x1638),
 * passes a record and integer selector to GetTxd and uses its byte
 * result (0x18A4..0x18BC), and ignores CurrLimit/RecvAuto results
 * (0x1890 / 0x1BA8). PDMTAPRES callback bodies confirm these inputs. */
extern void (*_padFuncNextPort)(int result);
extern int (*_padFuncGetTxd)(PadInfo2 *, int selector);
extern void (*_padFuncCurrLimit)(PadInfo2 *);
extern void (*_padFuncClrCmdNo)(PadInfo2 *);
extern int (*_padFuncSendAuto)(PadInfo2 *);
extern void (*_padFuncRecvAuto)(PadInfo2 *);

#endif
