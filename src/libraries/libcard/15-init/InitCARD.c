#include "common.h"

void ChangeClearPAD(long arg0);
int EnterCriticalSection(void);
void ExitCriticalSection(void);
void InitCARD2(long arg0);
s32 ReadInitPadFlag(void);
int VSync(int mode);
void _copy_memcard_patch(void);
void _patch_card(void);
void _patch_card2(void);
void _patch_card_info(void);

void InitCARD(long arg0) {
    s32 saved;

    ChangeClearPAD(0);
    VSync(0);
    saved = EnterCriticalSection();
    if (ReadInitPadFlag() == 0) {
        arg0 = 0;
    }
    InitCARD2(arg0);
    _copy_memcard_patch();
    _patch_card();
    _patch_card2();
    _patch_card_info();
    if (saved == 1) {
        ExitCriticalSection();
    }
}
