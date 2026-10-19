/* Original TU: library-input/psyq/LIB/LIBC2.LIB[18] STRCPY.OBJ
 * sha256: ac1a9baec29cd15fda538722bfdaf95ce22eccae5f8d818b7b46d3220b01ee8c
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strcpy
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

char *strcpy(char *arg0, const char *arg1) {
    char *temp_v1;
    char *var_v0;
    char temp_v0;

    var_v0 = 0;
    if (arg0 != 0) {
        temp_v1 = arg0;
        if (arg1 != 0) {
            temp_v0 = *arg1;
            arg1 += 1;
            arg0 += 1;
            *temp_v1 = temp_v0;
            if (temp_v0 != 0) {
                do {
                    temp_v0 = *arg1;
                    arg1 += 1;
                    *arg0 = temp_v0;
                    arg0 += 1;
                } while (temp_v0 != 0);
            }
            var_v0 = temp_v1;
        }
    }
    return var_v0;
}
