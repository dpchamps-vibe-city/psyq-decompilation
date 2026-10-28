#include "common.h"
#include "libpad-direct.h"
#include "libpad-enable-com.h"

/* PDRESRES owns the SIO engine state, its two per-channel result words and
 * the per-port mode initialiser. PDDIRRES NextPort indexes both the engine
 * state and the results by the current channel. (libpad-mtap.h carries the
 * same declarations but cannot be included from this member: it re-declares
 * _padFuncGetTxd with a different return type than libpad-direct.h.) */
extern int _padSioChan;
extern int _padSioState;
extern int _padFixResult[2];
int _padInitSioMode(PadInfo2 *);

/* PDDIRRES .data word 0x1F801040 (SIO0 base). NextPort reloads it each
 * iteration and clears the halfword control register at +0xA. */
extern volatile u8 *D_00000AB0;

/* The original caller passes the engine status as the second argument; the
 * matched definition in _dirFailAuto.c reads only the record. The K&R form
 * keeps the two-argument call site compilable against that definition. */
void _dirFailAuto();

void func_000001C8(int arg0) {
    PadInfo2 *info;
    u32 base;
    int chan;
    int res;
    int nofail;
    int *fix;
    volatile u8 *sio;

    base = (u32)B_00000AC0;
    nofail = -9;
    fix = _padFixResult;
    do {
        chan = _padSioChan;
        info = (PadInfo2 *)(chan * sizeof(PadInfo2) + base);
        if (arg0 != nofail) {
            if (arg0 == 0) {
                fix[chan] = 0;
            } else {
                _dirFailAuto(info, arg0);
                func_000002BC(info);
            }
        }
        sio = D_00000AB0;
        chan = _padSioChan + 1;
        _padSioState = 0;
        *(volatile u16 *)(sio + 0xA) = 0;
        _padSioChan = chan;
        if (_padChanStop >= chan) {
            res = _padInitSioMode((PadInfo2 *)(chan * sizeof(PadInfo2) + base));
            arg0 = 0xFFFF;
        } else {
            res = 1;
            arg0 = 0xFFFF;
        }
    } while (res == 0);
}
