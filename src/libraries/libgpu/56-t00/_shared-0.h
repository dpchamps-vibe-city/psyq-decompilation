/* Original TU: library-input/psyq/LIB/LIBGPU.LIB[56] T00.OBJ
 * sha256: 524133a364088bf8b93f1c468678226e83380d20782e6854b0a3f8a8bb633d98
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: OpenTIM, ReadTIM, func_000000EC
 */
#include "common.h"
#include "include_asm.h"


/* Original .bss reservation (16 bytes); the first word is the current TIM
 * address used by OpenTIM and ReadTIM. Static so the reduced original's
 * section-relative relocation is preserved instead of introducing a new
 * external symbol. */
static unsigned long *B_00000238;
