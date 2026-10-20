#include "common.h"

extern s16 _svm_damper;

void _SsVmDamperOn(void) {
    _svm_damper = 2;
}
