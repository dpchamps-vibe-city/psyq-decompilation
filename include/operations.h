#ifndef OPERATIONS_H
#define OPERATIONS_H

/*
 * Guarded unsigned divide-and-remainder.
 *
 * The PSY-Q library was assembled by the historical GNU MIPS assembler, whose
 * `divu rd,rs,rt` pseudo expanded to
 *
 *      divu $zero,rs,rt
 *      bnez rt, 1f
 *      nop
 *      break 7
 *  1:  mflo rd
 *
 * in that order, with an explicit delay-slot nop.  Modern GNU as (2.42) keeps
 * the divide-by-zero check but always emits
 *
 *      bnez rt, 1f
 *      divu $zero,rs,rt
 *      break 7
 *  1:  mflo rd
 *
 * i.e. the divide is placed in the branch delay slot and the nop disappears.
 * That is a different instruction sequence, not a different spelling of the
 * same program, and no C expression can select it.
 *
 * Original-code witness: libc2/33-prnt, the variable-divisor divmod at
 * 0x46C (original words divu/bnez/nop/break/mflo/mfhi).  Reproducing that
 * original expansion here makes the whole translation unit byte-identical
 * (1696/1696 .text bytes, 544/544 .rdata bytes measured through the
 * production assembler), while removing the operation produces a compiled
 * non-match.  The operand binding is the same as the SDK's compiler-generated
 * divmod (`divu rd,rs,rt; mfhi rd2`), which the original assembler guarded.
 *
 * ABI/effects: `acc` is divided by `den`; the quotient is written back to
 * `acc` (mflo), the remainder to `rem` (mfhi); hi/lo and memory are
 * clobbered.  The memory clobber is required: it keeps the compiler from
 * hoisting the caller's table-base load above the divide, which the original
 * schedule keeps after it.  This is a single statement operation, not a
 * function or a loop.
 */
#define UDIVMOD_GUARDED(acc, rem, den)                                                     \
    __asm__(".set noreorder\n\t"                                                           \
            "divu $zero,%0,%2\n\t"                                                         \
            "bnez %2,1f\n\t"                                                               \
            "nop\n\t"                                                                      \
            "break 7\n\t"                                                                  \
            "1:\n\t"                                                                       \
            "mflo %0\n\t"                                                                  \
            "mfhi %1\n\t"                                                                  \
            ".set reorder"                                                                 \
            : "+r"(acc), "=r"(rem)                                                         \
            : "r"(den)                                                                     \
            : "hi", "lo", "memory")

#endif /* OPERATIONS_H */
