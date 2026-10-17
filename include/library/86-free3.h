#ifndef LIBRARY_86_FREE3_H
#define LIBRARY_86_FREE3_H

#include "common.h"

/* Address-ordered heap block: offset 0 is the link, offset 4 is the size. */
typedef struct Block {
    struct Block *next;
    u32 size;
} Block;

/* Saved pre-modification state of a block, for realloc3 rollback. */
typedef struct {
    Block *bp;
    Block *next;
    u32 size;
} BlockReg;

extern Block *_freep;
extern BlockReg _r_bp;
extern BlockReg _r_p;
extern Block *_r_freep;

#endif
