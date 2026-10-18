/* Original TU: library-input/psyq/LIB/LIBC.LIB[46] SPRINTF.OBJ
 * sha256: c319155018f04ab800b4bb4b8003aac9046e29fd0a1bd5b1d139db3107bc20c7
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

static FmtSpec D_000009F0 = {0};

