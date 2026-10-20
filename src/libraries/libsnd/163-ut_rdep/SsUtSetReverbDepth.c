#include "common.h"
#include <libsnd.h>
#include <libspu.h>

extern SpuReverbAttr _svm_rattr;

void SsUtSetReverbDepth(short arg0, short arg1) {
    _svm_rattr.mask = 6;
    _svm_rattr.depth.left = (arg0 * 0x7FFF) / 127;
    _svm_rattr.depth.right = (arg1 * 0x7FFF) / 127;
    SpuSetReverbModeParam(&_svm_rattr);
}
