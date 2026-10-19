/* Original TU: QSORT.OBJ (LIBC2.LIB) */
#include "common.h"
#include <qsort.h>
/* Private byte-swap helper */
static void swap_bytes(void *left, void *right, u32 size);

void qsort(void *base, unsigned int count, unsigned int size, int (*compare)()) {
    unsigned char *first;
    unsigned char *partition;
    unsigned char *scan;
    size_t i;
    size_t lower_count;

    first = base;
    scan = first + size;
    lower_count = 0;
    if (count >= 2) {
        if (count == 2) {
            if (compare(first, scan) > 0) {
                swap_bytes(first, scan, size);
            }
        } else {
            swap_bytes(first, first + (count >> 1) * size, size);
            partition = first;
            for (i = 1; i < count; i++) {
                if (compare(scan, first) < 0) {
                    partition += size;
                    lower_count++;
                    if (scan != partition) {
                        swap_bytes(scan, partition, size);
                    }
                }
                scan += size;
            }
            if (partition != first) {
                swap_bytes(first, partition, size);
            }
            qsort(first, lower_count, size, compare);
            qsort(partition + size, count - lower_count - 1, size, compare);
        }
    }
}
static void swap_bytes(void *left, void *right, u32 size) {
    u32 i;
    u8 *right_ptr;
    u8 *left_ptr;
    u8 left_byte;
    u8 right_byte;

    i = 0;
    if (size != 0) {
        do {
            left_ptr = (u8 *) ((u8 *) left + i);
            right_ptr = (u8 *) ((u8 *) right + i);
            left_byte = *left_ptr;
            right_byte = *right_ptr;
            i += 1;
            *left_ptr = right_byte;
            *right_ptr = left_byte;
        } while (i < size);
    }
}
