#include "common.h"
#include <libsnd.h>

extern u32 _snd_vmask;

void SsSetVoiceMask(unsigned long arg0) {
    _snd_vmask = arg0;
}
