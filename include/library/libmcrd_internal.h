#ifndef LIBMCRD_INTERNAL_H
#define LIBMCRD_INTERNAL_H

/* LIBMCRD.OBJ retained diagnostic string at .rdata+0, MemCardExist use. */
extern char RO_STR_00001958[];

/* USERFUNC.OBJ Open stores a0 only; Execute passes a four-word state
 * record to that callback and tests its s32 return value. */
extern void UserFuncOpen(s32 (*callback)(s32 *));

#endif
