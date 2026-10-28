#include "common.h"
#include <memory.h>
#include "libpad-mtap.h"

static void func_00000188(PadInfo2 *);
static void func_000001FC(int);
static void func_00000314(PadInfo2 *);
static int func_00000358(PadInfo2 *, int);
static void func_00000468(PadInfo2 *);
static PadInfo2 *func_000006E4(int);
static int func_00000754(PadInfo2 *);
static void func_000009C4(PadInfo2 *);
static int func_000010F8(PadInfo2 *);

void _padInitMtapPort(void) {
    PadInfo2 *info;
    PadInfo2 *child;
    u8 *rx;
    u8 *tx;

    info = (PadInfo2 *)B_000011C0;
    bzero((u8 *)info, 0x1E0);
    child = (PadInfo2 *)B_000013A0;
    bzero((u8 *)child, 0x780);
    rx = B_00001B20;
    tx = B_00001B68;

    *(u8 **)&info[0].pad3A[2] = rx;
    rx += 0x23;
    *(u8 **)&info[0].pad3A[6] = tx;
    tx += 0x23;
    info[0].child = child;
    child += 4;
    *(u8 **)&info[1].pad3A[2] = rx;

    _padInfoDir = info;
    _padFuncNextPort = func_000001FC;
    _padFuncClrInfo = func_00000188;
    _padFuncGetTxd = func_00000358;
    _padFuncCurrLimit = func_00000468;
    _padFuncPort2Info = func_000006E4;
    _padFuncClrCmdNo = func_00000314;
    _padFuncSendAuto = func_00000754;
    _padFuncChkEng = func_000010F8;
    *(u8 **)&info[1].pad3A[6] = tx;
    info[1].child = child;
    _padFuncRecvAuto = func_000009C4;
}
