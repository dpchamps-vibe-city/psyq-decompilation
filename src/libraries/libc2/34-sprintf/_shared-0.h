/* Original TU: library-input/psyq/LIB/LIBC2.LIB[34] SPRINTF.OBJ
 * sha256: 1571d47c9218cd300aa56357aae40276a3c87f3b20c928936252d113f5479c4d
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: sprintf
 */
#include "common.h"
#include <stdarg.h>
#include <string.h>

typedef struct {
    unsigned int left : 1;
    unsigned int plus : 1;
    unsigned int alt : 1;
    unsigned int zero : 1;
    unsigned int hasprec : 1;
    unsigned int half : 1;
    unsigned int lng : 1;
    unsigned int dbl : 1;
    signed char sign;
    int width;
    int prec;
} FmtSpec;

typedef char *CharPtr;

static FmtSpec D_000009E0 = {0};

