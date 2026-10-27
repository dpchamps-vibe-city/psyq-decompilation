#include "common.h"

/* Retained member data at .bss+0x1D0 and .bss+0x1D4; the definitions are
 * owned by __library_member_data, not by this file. */
extern long B_000001D0;
extern long B_000001D4[];

/* Private helper defined later in the same original TU (MCXCMD23.OBJ at
 * .text+0x9C). */
int McxGetMcxInfo(int port, long *cmdBuf0, long *cmdBuf1);

int McxCardType(int port) {
    return McxGetMcxInfo(port, &B_000001D0, B_000001D4);
}
