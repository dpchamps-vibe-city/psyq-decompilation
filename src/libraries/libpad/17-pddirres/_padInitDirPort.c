#include "libpad-direct.h"
#include <memory.h>

static void func_00000160(PadInfo2 *);
static void func_000001C8(int);
static void func_000002BC(PadInfo2 *);
static u8 func_000002CC(PadInfo2 *);
static void func_00000388(PadInfo2 *);
static PadInfo2 *func_00000604(int);
static int func_00000624(PadInfo2 *);
static void func_00000734(PadInfo2 *);
static int func_00000A80(PadInfo2 *);

void _padInitDirPort(void) {
    bzero((unsigned char *)B_00000AC0, sizeof(B_00000AC0));
    B_00000AC0[0].data3C = B_00000CA0;
    B_00000AC0[0].data40 = B_00000CE8;
    B_00000AC0[1].data3C = B_00000CA0 + 0x23;
    _padInfoDir = B_00000AC0;
    B_00000AC0[1].data40 = B_00000CE8 + 0x23;
    _padFuncNextPort = func_000001C8;
    _padFuncClrInfo = func_00000160;
    _padFuncGetTxd = func_000002CC;
    _padFuncCurrLimit = func_00000388;
    _padFuncPort2Info = func_00000604;
    _padFuncClrCmdNo = func_000002BC;
    _padFuncSendAuto = func_00000624;
    _padFuncChkEng = func_00000A80;
    _padFuncRecvAuto = func_00000734;
}
