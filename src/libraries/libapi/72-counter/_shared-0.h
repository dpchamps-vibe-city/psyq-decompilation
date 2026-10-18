/* Original TU: library-input/psyq/LIB/LIBAPI.LIB[72] COUNTER.OBJ
 * sha256: 72cff5d7ae33c313a9b3dbfe40b9837e2c79edab6b26e83bcd384c93e14ec1b7
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

