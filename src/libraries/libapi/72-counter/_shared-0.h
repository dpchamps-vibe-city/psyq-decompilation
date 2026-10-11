/* Original TU: library-input/redux/libapi/72-counter.o[0] 72-counter.o
 * sha256: f9696b5b2525f5948c2e265374583b643e5fe7484870ce81a921db325f1c6c2b
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: SetRCnt, GetRCnt, StartRCnt, StopRCnt, ResetRCnt
 */
#include "common.h"
#include "include_asm.h"

/* Original counter accesses: u16 at 0/4/8, records stepped by 0x10.
 * D_000001E4 is the .data pointer initialized to MMIO 0x1F801100.
 * Storage remains in _data.c; this declaration supplies its source type. */
typedef struct RootCounterRegisters {
    u16 count;
    u16 pad2;
    u16 mode;
    u16 pad6;
    u16 target;
    u16 padA;
    u32 padC;
} RootCounterRegisters;

extern volatile RootCounterRegisters *D_000001E4;

