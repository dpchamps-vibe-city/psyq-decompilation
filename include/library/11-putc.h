#ifndef LIBRARY_11_PUTC_H
#define LIBRARY_11_PUTC_H

/* 11-putc.o calls the libapi `write` member (src/libraries/libapi/49-a53,
 * BIOS service 0x35). Declared here so this TU sees the matched signature. */
long write(long fd, void *buf, long count);

#endif
