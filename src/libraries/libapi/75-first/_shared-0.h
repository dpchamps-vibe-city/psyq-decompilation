/* Original TU: library-input/psyq/LIB/LIBAPI.LIB[75] FIRST.OBJ
 * sha256: b6bdf872b343258b83302382c2efb107035c93137afe64edddd52eac761ae24f
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: firstfile
 */
#include "common.h"
#include "include_asm.h"
#include "fs.h"

extern int (*B_00000310)();               /* saved device firstfile routine */
extern u8 B_00000318[];                   /* device-name buffer */
