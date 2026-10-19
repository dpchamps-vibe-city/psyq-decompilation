/* Original TU: library-input/psyq/LIB/LIBSPU.LIB[52] S_GTSA.OBJ
 * sha256: 338271e0b8859a65c6e70984504c8b0a8f7fd5afbcc63474bc30dff67fb50363
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: SpuGetTransferStartAddr
 */
#include "common.h"
#include "library/libspu_internal.h"

unsigned long SpuGetTransferStartAddr(void) {
    return (unsigned long)_spu_tsa << _spu_mem_mode_plus;
}
