/* Original TU: library-input/psyq/LIB/LIBC2.LIB[13] QSORT.OBJ
 * sha256: 2f00244d41eec9ce6990826ba55cc8652d7be82a6698daae5ea6a91cf1721143
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: qsort
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"
#include "13-qsort.h"

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
#include "common.h"

void func_000001B8(void *left, void *right, u32 size) {
    u32 var_a3;
    u8 *temp_a0;
    u8 *temp_v1;
    u8 temp_a1;
    u8 temp_v0;

    var_a3 = 0;
    if (size != 0) {
        do {
            temp_v1 = (u8 *) ((u8 *) left + var_a3);
            temp_a0 = (u8 *) ((u8 *) right + var_a3);
            temp_a1 = *temp_v1;
            temp_v0 = *temp_a0;
            var_a3 += 1;
            *temp_v1 = temp_v0;
            *temp_a0 = temp_a1;
        } while (var_a3 < size);
    }
}
