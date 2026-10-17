#ifndef LIBRARY_3_GETC_H
#define LIBRARY_3_GETC_H

/* 3-getc.o calls the libapi `read` member (src/libraries/libapi/48-a52,
 * BIOS service 0x34). Declared here so this TU sees the matched signature. */
long read(long fd, void *buf, long count);

#endif
