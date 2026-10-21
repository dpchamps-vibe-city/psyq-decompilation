#include "common.h"

typedef struct {
    s32 active;      /* 0x00 */
    u8 command;      /* 0x04 */
    u8 param[4];     /* 0x05 */
    u8 pad0[3];      /* 0x09 */
    u8 *param_ptr;   /* 0x0C */
    u8 pad1[0x1C];   /* 0x10 */
    u8 lastcom;      /* 0x2C */
    u8 pad2[0x0A];   /* 0x2D */
    u8 mode;         /* 0x37 */
    u8 pad3[0x0C];   /* 0x38 */
    s32 timeout;     /* 0x44 */
    s32 unk44;       /* 0x48 */
    u8 pad4[4];      /* 0x4C */
    u8 unk38;        /* 0x50 */
    u8 unk39;        /* 0x51 */
} DsRoot;

extern DsRoot D_00001240r __asm__("D_00001240");
extern s32 D_00001294[];

extern void CD_flush(void);
extern s32 CD_cw(s32 com, u8 *param, u8 *result, s32 mode);
extern void parcpy(u8 *dst, u8 *src);

static s32 func_000003B8(u8 com, u8 *param) {
    s32 t;

    CD_flush();
    D_00001240r.command = com;
    if (param != 0) {
        parcpy(D_00001240r.param, param);
        D_00001240r.param_ptr = D_00001240r.param;
    } else {
        D_00001240r.param_ptr = 0;
    }
    D_00001240r.timeout = (t = D_00001294[D_00001240r.command]) ? t * 0x3C : 0x1E;
    D_00001240r.unk44 = 0;
    switch (D_00001240r.command) {
    case 9:
        if (D_00001240r.unk38 != 0 && D_00001240r.unk39 == D_00001240r.command) {
            D_00001240r.command = 1;
        }
        break;
    case 7:
        if (D_00001240r.mode == 1) {
            D_00001240r.command = D_00001240r.mode;
        }
        break;
    case 8:
        if (D_00001240r.mode != 1) {
            D_00001240r.command = 1;
        }
        break;
    }
    if (D_00001240r.command == 1) {
        D_00001240r.param_ptr = 0;
        D_00001240r.timeout = (t = D_00001294[D_00001240r.command]) ? t * 0x3C : 0x1E;
    }
    if (CD_cw(D_00001240r.command, D_00001240r.param_ptr, 0, 1) != 0) {
        D_00001240r.unk44 = 0;
        D_00001240r.timeout = 0;
        return 0;
    }
    D_00001240r.lastcom = D_00001240r.command;
    if (D_00001240r.command != 1) {
        D_00001240r.unk39 = D_00001240r.command;
        D_00001240r.unk38 = 0;
    }
    return 1;
}
