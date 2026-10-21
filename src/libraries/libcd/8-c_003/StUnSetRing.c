#include "common.h"

/* The original member's .data holds the four CD-ROM register addresses at
 * .data+0 and .data+12; the extracted data part defines them under these
 * listing names. */
extern volatile u8 *D_000000F0;
extern volatile u8 *D_000000FC;

extern s32 EnterCriticalSection(void);
extern void ExitCriticalSection(void);
extern void (*DsDataCallback(void (*func)()))();
extern void (*DsReadyCallback(void (*func)()))();
extern void (*CdDataCallback(void (*func)()))();
extern void (*CdReadyCallback(void (*func)()))();
extern s32 DS_active;

void StUnSetRing(void) {
    EnterCriticalSection();
    if (DS_active == 1) {
        DsDataCallback(0);
        DsReadyCallback(0);
    } else {
        CdDataCallback(0);
        CdReadyCallback(0);
    }
    *D_000000F0 = 0;
    *D_000000FC = 0;
    ExitCriticalSection();
}
