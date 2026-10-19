/* Original TU: library-input/psyq/LIB/LIBSND.LIB[59] SSGNC.OBJ */
#include <libsnd.h>
#include <libspu.h>

short SsGetNck(void) {
    return SpuGetNoiseClock();
}
