#ifndef LIBRARY_API_PAD_PATCH_H
#define LIBRARY_API_PAD_PATCH_H

#include "common.h"

typedef s32 (*ApiPadPatchHandler)(void);

/* LIBAPI PAD.OBJ owns the 16-byte common symbol _apiPadPatch.
 * Original .text relocations address the queue word at +0, the two-handler
 * array at +4 (stores at +0/+4), and the final word at +12 independently.
 * These declarator labels name those storage views; they emit no code and
 * introduce no additional linker symbols or storage. */
extern u32 apiPadPatchNext __asm__("_apiPadPatch");
extern ApiPadPatchHandler apiPadPatchHandlers[2] __asm__("_apiPadPatch+4");
extern u32 apiPadPatchReserved __asm__("_apiPadPatch+12");

int EnterCriticalSection(void);
void ExitCriticalSection(void);
int SysDeqIntRP(int priority, void *rp);
int SysEnqIntRP(int priority, void *rp);

#endif
