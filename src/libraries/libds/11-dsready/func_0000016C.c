#include "common.h"

typedef struct {
    u_char minute;
    u_char second;
    u_char sector;
    u_char track;
} DslLOC;

extern DsReadyState D_00000610;
extern DslCB D_00000624;
extern DslRCB D_00000628;
extern s32 D_00000630;

DslLOC *DS_lastpos(void);
u_char DS_lastmode(void);
void func_00000500(void);

DslCB DsDataCallback(DslCB func);
int DsGetSector(void *madr, int size);
int DsPosToInt(DslLOC *p);
int DsQueueLen(void);

void func_0000016C(u_char arg0, u_char *arg1) {
    u_long sp10[4];
    DslCB cb;
    s32 pos;

    if (D_00000610.pos == -1) {
        D_00000610.pos = DsPosToInt(DS_lastpos());
    }
    arg0 = arg0 & 0xFF;
    if (arg0 == 1) {
        if (DS_lastmode() & 0x20) {
            cb = DsDataCallback(0);
            DsGetSector(&sp10, 3);
            DsDataCallback(cb);
            pos = DsPosToInt((DslLOC *) &sp10);
            if (pos != D_00000610.pos) {
                D_00000610.unkC = 1;
                goto tail;
            }
            if ((D_00000610.func != 0) && (D_00000610.unk4 < pos)) {
                D_00000610.func(1, arg1, sp10);
                D_00000610.unk4 = pos;
            }
        } else {
            if ((D_00000610.func != 0) && (D_00000610.pos > D_00000610.unk4)) {
                D_00000610.func(1, arg1, sp10);
                D_00000610.unk4 = D_00000610.pos;
            }
        }
        D_00000610.pos++;
    } else if (arg0 == 4) {
        if (D_00000610.func != 0) {
            D_00000610.func(4, arg1, sp10);
        }
    } else if (*arg1 & 0x10) {
        if (D_00000610.mode == 1) {
            DsReadyCallback(0);
            return;
        }
        DsReadyCallback(D_00000610.ready);
        DsStartCallback(D_00000610.start);
        D_00000610.active = 0;
        if (D_00000610.func != 0) {
            D_00000610.func(arg0, arg1, sp10);
        }
        return;
    } else if ((DsQueueLen() == 0) && !(*arg1 & 0xA0)) {
        D_00000610.unkC = 1;
    }
tail:
    if (D_00000610.unkC == 1) {
        if ((D_00000610.count > 0) || (D_00000610.count == -1)) {
            func_00000500();
            if (D_00000610.count > 0) {
                D_00000610.count--;
            }
        } else {
            if (D_00000630 == D_00000610.unkC) {
                DsReadyCallback(D_00000624);
                DsStartCallback(D_00000628);
                DsCommand(9, 0, 0, -1);
            }
            D_00000630 = 0;
            if (D_00000610.func != 0) {
                D_00000610.func(5, arg1, sp10);
            }
        }
        D_00000610.unkC = 0;
    }
}
