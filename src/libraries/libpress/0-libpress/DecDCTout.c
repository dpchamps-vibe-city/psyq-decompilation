#include "common.h"
#include <sys/types.h>
#include <libpress.h>

static void func_000004B8(u_long *buf, int size);

void DecDCTout(u_long *buf, int size) {
    func_000004B8(buf, size);
}
