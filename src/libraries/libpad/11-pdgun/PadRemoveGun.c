#include "common.h"
#include <libapi.h>
#include <libpad.h>
#include "libpad-internal.h"

void PadRemoveGun(void) {
    volatile u32 *istat;

    istat = (volatile u32 *)0x1F801070;
    EnterCriticalSection();
    _padGunExec = 0;
    _padFuncIntGun = 0;
    _padFuncSetGunPort = 0;
    _padFuncGetGunPos = 0;
    if (_padGunSavePadPtr[0] != 0) {
        _padGunSavePadPtr[0]->actTable = _padGunSaveTxBuf[0];
        _padGunSavePadPtr[0]->actSize = _padGunSaveTxLen[0];
        _padGunSavePadPtr[0] = 0;
        _padGunSaveTxBuf[0] = 0;
    }
    if (_padGunSavePadPtr[1] != 0) {
        _padGunSavePadPtr[1]->actTable = _padGunSaveTxBuf[1];
        _padGunSavePadPtr[1]->actSize = _padGunSaveTxLen[1];
        _padGunSavePadPtr[1] = 0;
        _padGunSaveTxBuf[1] = 0;
    }
    istat[1] &= ~0x400;
    istat[0] &= ~0x400;
    _padGunExitHook();
    ExitCriticalSection();
}
