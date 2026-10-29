#ifndef LIBPRESS_INTERNAL_H
#define LIBPRESS_INTERNAL_H

#include "common.h"
#include <sys/types.h>

/* LIBPRESS.OBJ native relocations at 0x6B4, 0x6C4 and 0x6A4. */
extern s32 *D_00000870;
extern volatile u_long *D_0000087C;
extern volatile u32 *D_0000089C;
/* Format string at .rdata+0x3C in the original member. */
extern char RO_STR_00000708[];

/* Native 0x6D0 establishes the zero result; both callers ignore it. */
static int func_00000684(char *msg);

#endif
