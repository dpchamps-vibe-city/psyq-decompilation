#include "common.h"
#include "library/11-putc.h"

void putc(s8 c, long fd) {
    write(fd, &c, 1);
}
