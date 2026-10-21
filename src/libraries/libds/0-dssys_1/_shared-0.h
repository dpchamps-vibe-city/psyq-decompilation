/* Original TU: library-input/psyq/LIB/LIBDS.LIB[0] DSSYS_1.OBJ
 * sha256: 3a83d7b870e0412f18e9865cd5cdd0af0b9b692e18518f41e0da8683b9f9f08f
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: DS_init, DS_reset_members, DS_close, DS_cw, DS_vsync_callback, DS_sync_callback, DS_ready_callback, DS_start_callback, DS_system_status, DS_lastcom, DS_lastmode, DS_lastpos, DS_lastseek, DS_lastread, DS_status, DS_shell_open, DS_cw_system, func_000003B8, func_00000590, func_00000860, func_000008E8, func_000009F8, func_00000BDC, func_00000E64, func_00000F50, func_00000FE4, DS_stop, DS_restart, DS_system_active, parcpy, rescpy
 */
#include "common.h"
#include "include_asm.h"

typedef void (*DslCB)(u8, u8 *);

typedef struct {
    u8 minute;
    u8 second;
    u8 sector;
    u8 track;
} DslLOC;

/* The library's command and drive state (.data 0x1240). */
typedef struct {
    s32 active;
    u8 command;             /* 0x04 */
    u8 param[4];            /* 0x05 */
    u8 pad9[3];
    u8 *param_ptr;          /* 0x0C */
    u8 result[8];           /* 0x10 */
    u8 status;              /* 0x18 */
    u8 pad19[3];
    s32 unk1C;              /* 0x1C */
    s32 system[3];          /* 0x20: DS_system_status */
    u8 lastcom;             /* 0x2C */
    u8 lastmode;            /* 0x2D */
    DslLOC lastpos;         /* 0x2E */
    u8 lastseek;            /* 0x32 */
    u8 lastread;            /* 0x33 */
    u8 flags[4];            /* 0x34 */
    s32 unk38;              /* 0x38 */
    s32 shell_open;         /* 0x3C */
    s32 unk40;              /* 0x40 */
    s32 timeout;            /* 0x44 */
    s32 unk48;              /* 0x48 */
    s32 unk4C;              /* 0x4C */
    u8 unk50;               /* 0x50 */
    u8 unk51;               /* 0x51 */
} DsState;

extern s32 D_00001238[2];
extern DsState D_00001240;
extern s32 D_00001294[32];  /* per command: timeout in seconds, 0 for the default */
extern s32 D_00001314[32];
extern s32 D_00001394;
extern volatile DslCB B_00001398;   /* vsync */
extern volatile DslCB B_0000139C;   /* sync */
extern volatile DslCB B_000013A0;   /* ready */
extern volatile DslCB B_000013A4;   /* start */

