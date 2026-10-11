#ifndef LIBSPU_INTERNAL_H
#define LIBSPU_INTERNAL_H

#include "common.h"

extern s32 _spu_mem_mode_plus;
extern u16 _spu_tsa;

/* Public signature from the SDK's LIBSPU.H. */
unsigned long SpuGetTransferStartAddr(void);

#endif
