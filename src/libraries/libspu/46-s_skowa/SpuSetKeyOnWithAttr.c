#include "common.h"
#include <libspu.h>

void SpuSetKeyOnWithAttr(SpuVoiceAttr *attr) {
    SpuSetVoiceAttr(attr);
    SpuSetKey(1, attr->voice);
}
