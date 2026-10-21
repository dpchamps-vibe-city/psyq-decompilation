#include "common.h"

typedef unsigned char u_char;
typedef unsigned long u_long;

typedef struct {
    u_char minute;
    u_char second;
    u_char sector;
    u_char track;
} DslLOC;

typedef void (*DslCB)(u_char, u_char *);

typedef struct {
    u_long size;        /* 0x580 */
    u_long *buf;        /* 0x584 */
    int sectors;        /* 0x588 */
    int mode;           /* 0x58C */
    int pad0;           /* 0x590 */
    DslCB callback;     /* 0x594 */
    int vsync;          /* 0x598 */
    int pad1;           /* 0x59C */
    int active;         /* 0x5A0 */
} DsReadParam;

extern DsReadParam D_00000580;

s32 ER_active(void);
DslLOC *DsLastPos(DslLOC *p);
int DsPacket(u_char mode, DslLOC *pos, u_char com, DslCB func, int count);
int VSync(int mode);
DslCB DsDataCallback(DslCB func);

static void func_000001A0(u_char, u_char *);
static void func_0000034C(u_char, u_char *);

int DsRead(DslLOC *pos, int sectors, u_long *buf, int mode) {
    DslLOC loc;
    int ret = 0;

    if (D_00000580.active == 1) {
        return ret;
    }
    if (ER_active() != 0) {
        return ret;
    }
    D_00000580.size = 0x200;
    D_00000580.buf = buf;
    D_00000580.sectors = sectors;
    if (pos == 0) {
        loc = *DsLastPos(0);
    } else {
        loc = *pos;
    }
    mode |= 0x20;
    ret = DsPacket(mode & 0xFF, &loc, 6, func_000001A0, -1);
    if (ret == 0) {
        return 0;
    }
    D_00000580.vsync = VSync(-1);
    if (D_00000580.mode & 1) {
        D_00000580.callback = DsDataCallback(func_0000034C);
    }
    D_00000580.active = 1;
    return ret;
}
