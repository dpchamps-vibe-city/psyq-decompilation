#ifndef LIBRARY_LIBGTE_PPMFT_H
#define LIBRARY_LIBGTE_PPMFT_H

/* PPMFT.OBJ: StoreImage/LoadImage use the original word buffer at B_00001D00. */
extern unsigned long B_00001D00[];
/* Original retained .rdata contains the area-zero diagnostic at 0x1CC0. */
extern char RO_STR_00001CC0[];
/* Original PPMFT .rdata at 0x1CD8: invalid row/column diagnostic. */
extern char RO_STR_00001CD8[];

/* SCAN.OBJ ScanXY0: PPMFT's original call stores arguments 4..13 at sp+10..34. */
extern void ScanXY0(int, int, int, int, int, int, int,
                    unsigned long **, int *, int *, int *, int *, int,
                    unsigned short *);

#endif
