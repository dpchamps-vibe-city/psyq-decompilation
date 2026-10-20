#include "common.h"
#include <libsnd.h>

extern s8 _svm_auto_kof_mode;

void SsSetAutoKeyOffMode(short mode) {
    _svm_auto_kof_mode = (s8) mode;
}
