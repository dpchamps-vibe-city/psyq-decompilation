#ifndef GLOBALS_OVERRIDE_H
#define GLOBALS_OVERRIDE_H

/* Project-owned global type overrides. No target layouts are supplied. */

typedef struct {
    unsigned int unk0;
    unsigned int unk4;
    unsigned int unk8;
    unsigned int unkC;
    unsigned int unk10;
    unsigned int unk14;
    unsigned int unk18;
    unsigned int unk1C;
    unsigned int unk20;
    unsigned int unk24;
} Obj;

extern Obj *D_000003A0;

/* Debug level owned by the libcd BIOS_1 member (Libcd.lib[20] CD_debug);
 * referenced by TOC.OBJ (Libcd.lib[1]) for its trace printing. */
extern int CD_debug;

#endif
