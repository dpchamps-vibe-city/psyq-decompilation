#include "common.h"
#include "52-qsort.h"

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
                func_000001B8(first, scan, size);
            }
        } else {
            func_000001B8(first, first + (count >> 1) * size, size);
            partition = first;
            for (i = 1; i < count; i++) {
                if (compare(scan, first) < 0) {
                    partition += size;
                    lower_count++;
                    if (scan != partition) {
                        func_000001B8(scan, partition, size);
                    }
                }
                scan += size;
            }
            if (partition != first) {
                func_000001B8(first, partition, size);
            }
            qsort(first, lower_count, size, compare);
            qsort(partition + size, count - lower_count - 1, size, compare);
        }
    }
}
