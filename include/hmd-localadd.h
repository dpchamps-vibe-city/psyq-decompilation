#ifndef HMD_LOCALADD_H
#define HMD_LOCALADD_H

/*
 * Operation macros used by the original HMD library source.
 *
 * Token-identical to library-input/psyq/SRC/LIB/HMD/LOCALADD.H (Sony,
 * "Run-time Library Release 4.4"), which is the local addition header the
 * original 04010010.C translation unit included.  These read/write GTE
 * registers through register operands (mtc2/mfc2), which the pointer-based
 * inline_c.h helpers do not express; the nops are the R3000 interlock, part
 * of the operation rather than scheduling slack.
 */

typedef struct {
	long	vx;
	long	vy;
	long	vz;
} LVECTOR;

#define gte_ldlvl_1( r0 ) __asm__ volatile (			\
	"mtc2	%0, $9"					\
	:							\
	: "r"( r0 ) )

#define gte_ldlvl_2( r0 ) __asm__ volatile (			\
	"mtc2	%0, $10"					\
	:							\
	: "r"( r0 ) )

#define gte_ldlvl_3( r0 ) __asm__ volatile (			\
	"mtc2	%0, $11"					\
	:							\
	: "r"( r0 ) )

#define gte_stmac_1() ({ u_long __value;\
	__asm__ volatile (			\
	".set noreorder;"			\
	"mfc2	%0, $25;"					\
	"nop;"					\
	".set reorder"				\
	: "=r"( __value ) :);\
	__value;})

#define gte_stmac_2() ({ u_long __value;\
	__asm__ volatile (			\
	".set noreorder;"			\
	"mfc2	%0, $26;"					\
	"nop;"					\
	".set reorder"				\
	: "=r"( __value ) :);\
	__value;})

#define gte_stmac_3() ({ u_long __value;\
	__asm__ volatile (			\
	".set noreorder;"			\
	"mfc2	%0, $27;"					\
	"nop;"					\
	".set reorder"				\
	: "=r"( __value ) :);\
	__value;})

#define gte_lzc_nom( r0 ) ({ u_long __value;\
	__asm__ volatile (			\
	".set noreorder;"			\
	"mtc2	%1, $30;"			\
	"nop;"					\
	"nop;"					\
	"mfc2	%0, $31;"			\
	"nop;"					\
	".set reorder"				\
	: "=r"( __value ) \
	: "r"( r0 ) ); \
	__value;})

#endif
