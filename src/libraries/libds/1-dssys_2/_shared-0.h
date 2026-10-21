/* Original TU: library-input/psyq/LIB/LIBDS.LIB[1] DSSYS_2.OBJ
 * sha256: f454002a591b4be92d45328c8012cc3bd3ced82d5958a209e1949d6742035a7e
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: func_00000088, func_000000B8, DS_CQ_flush, func_00000204, func_0000028C, func_0000047C, func_00000710, DsInit, DsReset, DsCommand, DsPacket, _DsPacket2, DsSync, DsReady, DsQueueLen
 */
#include "common.h"
#include "include_asm.h"

/* A queued command, and the ring of eight the queue functions share. */
typedef struct {
    s32 active;
    u8 command;
    u8 param[4];
    u8 pad[3];
    s32 unkC;
    s32 unk10;
    s32 unk14;
} DsCommand;

typedef struct {
    DsCommand command[8];
    s32 index;
    s32 field4;
    s32 count;
} DsCq;

/* The last response to a command, kept per interrupt class. */
typedef struct {
    s32 active;
    u8 command;
    u8 param[8];
} DsInitCmd;

