#ifndef LIBRARY_LIBPAD_GUN_HOOK_H
#define LIBRARY_LIBPAD_GUN_HOOK_H

#include "common.h"

/* PDHOKRES reserves four bytes here; _padGetHitCount loads the word and
 * _padClrHitCount clears it with a word store. */
extern s32 B_00000310;

#endif
