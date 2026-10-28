#ifndef LIBRARY_LIBPAD_ENABLE_COM_H
#define LIBRARY_LIBPAD_ENABLE_COM_H

#include "libpad-internal.h"
#include <libpad.h>

/* PDRESRES .data+0x40/+0x58/+0x5C define the word flags.
 * _padRestPeriod is its 8-byte common object; _padIntPad increments
 * and compares both word elements with signed slti. */
extern int _padIntExec;
extern int _padChanStart;
extern int _padChanStop;
extern int _padRestPeriod[2];

#endif
