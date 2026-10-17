/* Original TU: library-input/redux/libc2/33-prnt.o[0] 33-prnt.o
 * sha256: 71f18d140748b41bcccbcb1b7d14c41136b84c78674f7a458db1a630d7fd06d5
 * One original member, one TU.  prnt.c now emits the member's read-only data
 * (the two digit tables, the "(null)" literal and the conversion jump table);
 * only the original 12-byte .rdata tail padding remains here.
 */
#include "common.h"

static const u8 rdata_tail_pad[12] = {0};
