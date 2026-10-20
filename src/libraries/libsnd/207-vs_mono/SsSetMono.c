#include "common.h"
#include <libsnd.h>

extern s16 _svm_stereo_mono;

void SsSetMono(void) {
    _svm_stereo_mono = 1;
}
