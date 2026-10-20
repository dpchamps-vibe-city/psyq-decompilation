#include "common.h"
#include <sys/types.h>
#include <libds.h>

s32 DS_shell_open();                                /* extern */

int DsShellOpen(void) {
    return DS_shell_open();
}
