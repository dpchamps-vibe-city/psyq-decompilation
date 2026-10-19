/* S_GTSA.OBJ - SpuGetTransferStartAddr */
#include "library/libspu_internal.h"

unsigned long SpuGetTransferStartAddr(void) {
    return (unsigned long)_spu_tsa << _spu_mem_mode_plus;
}
