#include "common.h"

u_char DS_lastread(void);
int DsPacket(u_char mode, DslLOC *pos, u_char com, DslCB func, int count);
static void func_00000578(u_char, u_char *);

void func_00000500(void) {
    DslLOC *temp_s1;
    s32 temp_s0;

    DsReadyCallback(0);
    D_00000610.pos = DsPosToInt(DS_lastpos());
    temp_s0 = DS_lastmode() & 0xFF;
    temp_s1 = DS_lastpos();
    DsPacket(temp_s0, temp_s1, DS_lastread() & 0xFF, func_00000578, -1);
}
