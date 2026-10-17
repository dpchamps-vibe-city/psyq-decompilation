/* Original TU: library-input/redux/libc2/34-sprintf.o[0] 34-sprintf.o
 * sha256: c356b7fcc080d3fcb3d73165d9fdafe5422e8b7aa62e6d7a7e98c8d778ae5695
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
static const unsigned char upper_digits[] = "0123456789ABCDEF";
static const unsigned char lower_digits[] = "0123456789abcdef";

