# inline_a.inc: GTE command macros for GNU as, named after Sony's INLINE_A.H
# ("Macro definitions of DMPSX version 3 for Assembler programs", PSY-Q
# Run-time Library Release 4.7, library-input/psyq/INCLUDE/INLINE_A.H).
#
# INLINE_A.H emitted placeholder words that DMPSX later patched into real
# coprocessor-2 commands.  GNU as needs no patch step, so each macro here
# assembles the command word directly.  Names, parameter lists and parameter
# order follow INLINE_A.H exactly.  INLINE_A.H also defined n-prefixed forms
# (nRTPT ...) that carry two leading hazard nops; they are not reproduced
# here because gas macro names are case-insensitive, so nOP would capture
# every plain nop.  The reconstructed sources write their hazard nops out,
# as the original bytes place them.
#
#   RTPS RTPT DCPL DPCS DPCT INTPL NCS NCT NCDS NCDT NCCS NCCT CDP CC
#   NCLIP AVSZ3 AVSZ4    MVMVA sf,mx,v,cv,lm    SQR sf    OP sf    GPF sf    GPL sf

.ifndef .L_INLINE_A_INC
.L_INLINE_A_INC:

.macro GTECMD fake, op, sf = 1, mx = 0, v = 0, cv = 0, lm = 0
	cop2	\fake << 20 | \sf << 19 | \mx << 17 | \v << 15 | \cv << 13 | \lm << 10 | \op
.endm

.macro RTPS
	GTECMD	0x01, 0x01
.endm
.macro RTPT
	GTECMD	0x02, 0x30
.endm
.macro DCPL
	GTECMD	0x06, 0x29
.endm
.macro DPCS
	GTECMD	0x07, 0x10
.endm
.macro DPCT
	GTECMD	0x0F, 0x2A
.endm
.macro INTPL
	GTECMD	0x09, 0x11
.endm
.macro NCS
	GTECMD	0x0C, 0x1E, lm = 1
.endm
.macro NCT
	GTECMD	0x0D, 0x20, lm = 1
.endm
.macro NCDS
	GTECMD	0x0E, 0x13, lm = 1
.endm
.macro NCDT
	GTECMD	0x0F, 0x16, lm = 1
.endm
.macro NCCS
	GTECMD	0x10, 0x1B, lm = 1
.endm
.macro NCCT
	GTECMD	0x11, 0x3F, lm = 1
.endm
.macro CDP
	GTECMD	0x12, 0x14, lm = 1
.endm
.macro CC
	GTECMD	0x13, 0x1C, lm = 1
.endm
.macro NCLIP
	GTECMD	0x14, 0x06, sf = 0
.endm
.macro AVSZ3
	GTECMD	0x15, 0x2D
.endm
.macro AVSZ4
	GTECMD	0x16, 0x2E
.endm
.macro MVMVA sf, mx, v, cv, lm
	GTECMD	0x04, 0x12, sf = \sf, mx = \mx, v = \v, cv = \cv, lm = \lm
.endm
.macro SQR sf
	GTECMD	0x0A, 0x28, sf = \sf, lm = 1
.endm
.macro OP sf
	GTECMD	0x17, 0x0C, sf = \sf
.endm
.macro GPF sf
	GTECMD	0x19, 0x3D, sf = \sf
.endm
.macro GPL sf
	GTECMD	0x1A, 0x3E, sf = \sf
.endm

.endif
