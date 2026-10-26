#ifndef LIBGTE_REGS_H
#define LIBGTE_REGS_H

/*
 * GTE control-register reads for the depth-cue parameters.
 *
 * The original libgte members read DQA ($27, C2_DQA in gtereg.h) and DQB
 * ($28, C2_DQB) with cfc2 followed by one interlock nop, the same shape as the
 * SDK's C-side read sequences in inline_c.h (gte_ReadGeomScreen etc.). The
 * R3000 needs the nop between cfc2 and the next instruction that uses the
 * transferred value, so it is part of the operation, not scheduling slack.
 */
#define gte_ReadDQA(out) __asm__ volatile("cfc2 %0, $27; nop" : "=r"(out))
#define gte_ReadDQB(out) __asm__ volatile("cfc2 %0, $28; nop" : "=r"(out))

#endif
