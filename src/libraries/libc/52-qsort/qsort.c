/* QSORT.OBJ \u2014 LIBC.LIB member 52 */
#include "common.h"
#include <qsort.h>

static void swap(void *left, void *right, u32 size);

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
                swap(first, scan, size);
            }
        } else {
            swap(first, first + (count >> 1) * size, size);
            partition = first;
            for (i = 1; i < count; i++) {
                if (compare(scan, first) < 0) {
                    partition += size;
                    lower_count++;
                    if (scan != partition) {
                        swap(scan, partition, size);
                    }
                }
                scan += size;
            }
            if (partition != first) {
                swap(first, partition, size);
            }
            qsort(first, lower_count, size, compare);
            qsort(partition + size, count - lower_count - 1, size, compare);
        }
    }
}
static void swap(void *left, void *right, u32 size) {
    unsigned char tmp;
    u32 i;

    for (i = 0; i < size; i++) {
        tmp = ((unsigned char *)left)[i];
        ((unsigned char *)left)[i] = ((unsigned char *)right)[i];
        ((unsigned char *)right)[i] = tmp;
    }
}
