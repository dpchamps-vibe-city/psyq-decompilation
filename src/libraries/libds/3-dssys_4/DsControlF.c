#include "common.h"
#include <sys/types.h>
#include <libds.h>

int DsControlF(u_char com, u_char*param) {
    return DsCommand(com & 0xFF, param, NULL, 0);
}
