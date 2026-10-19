/* Original TU: PUTC.OBJ (LIBC2.LIB[11])
 */
#include <stdio.h>
#include <libapi.h>

void putc(char c, int fd) {
    write(fd, &c, 1);
}
