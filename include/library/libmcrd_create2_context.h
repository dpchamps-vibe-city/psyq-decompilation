#ifndef LIBMCRD_CREATE2_CONTEXT_H
#define LIBMCRD_CREATE2_CONTEXT_H

#include "common.h"

/* LOW.OBJ access witnesses: directory stride 32, words at +0/+4,
 * unsigned halfword at +8, and the 20-byte name at +10. Separate
 * section-relative views are hypotheses verified through the member oracle,
 * not a claim that the whole .bss section was one source-level object. */
typedef struct {
    u32 type;
    u32 size;
    u16 next;
    char name[20];
} McrdLowDirectoryEntry;

extern McrdLowDirectoryEntry B_00000B18[];
extern s8 B_00000D48[];
extern u8 B_00000D58[];
extern char RO_STR_00000B08[];

#endif
