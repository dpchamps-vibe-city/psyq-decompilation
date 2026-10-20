#include "common.h"

extern s16 _svm_damper;

void _SsVmDamperOff(void) {
    _svm_damper = 0;
}
