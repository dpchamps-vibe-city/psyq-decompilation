#include "common.h"
#include <libpad.h>

extern u8 _padGunEnalePort;

void PadEnableGun(unsigned char arg0) {
    _padGunEnalePort = arg0;
}
