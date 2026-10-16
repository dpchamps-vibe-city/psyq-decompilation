#include "common.h"

extern void StartPAD2(void);                        /* extern */
extern void EnablePAD(void);                        /* extern */
void ChangeClearPAD(long arg0);

s32 StartPAD(void) {
    StartPAD2();
    ChangeClearPAD(0);
    EnablePAD();
    return 1;
}
