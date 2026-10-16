#include "common.h"

extern s32 D_00000300;

void _remove_ChgclrPAD(void);
void _patch_pad(void);
void InitPAD2(char *buf1, long siz1, char *buf2, long siz2);
int func_000001DC(void);                            /* static */
int EnterCriticalSection(void);
void ExitCriticalSection(void);
void ChangeClearPAD(long arg0);

void InitPAD(char *buf1, long siz1, char *buf2, long siz2) {
    _remove_ChgclrPAD();
    EnterCriticalSection();
    _patch_pad();
    ExitCriticalSection();
    ChangeClearPAD(0);
    func_000001DC();
    InitPAD2(buf1, siz1, buf2, siz2);
    D_00000300 = 1;
}
