#include "common.h"

extern volatile u8 *LD_00000B88 asm("$LD_00000B88");
extern volatile u8 *LD_00000B90 asm("$LD_00000B90");
extern volatile u8 *LD_00000B94 asm("$LD_00000B94");
extern volatile u32 *LD_00000B98 asm("$LD_00000B98");
extern volatile u32 *LD_00000B9C asm("$LD_00000B9C");
extern volatile u32 *LD_00000BA8 asm("$LD_00000BA8");
extern volatile u32 *LD_00000BB8 asm("$LD_00000BB8");
extern volatile u16 *B_00000BD8 asm("$LB_00000BD8");

extern s32 StFinalSector;
extern s32 StRgb24;
extern s32 StCdIntrFlag;
extern u8 *StEmu_Addr;
extern s32 StEmu_Idx;
extern s32 StRingIdx1;
extern s32 StRingIdx2;
extern s32 StRingSize;
extern s32 StMode;
extern s32 StSTART_FLAG;
extern s32 StStartFrame;
extern s32 CChannel;
extern s32 StCHANNEL;
extern s32 Stframe_no;
extern s32 StEndFrame;
extern s16 Stsector_offset;
extern u16 *StRingAddr;
extern u32 *StRingBase;
extern void (*StFunc2)();
extern s32 debug_cause;

extern int CdReady(int, u8 *);
extern void init_ring_status(s32, s32);
extern void data_ready_callback(void);
typedef struct { u8 b[4]; } Word4;

extern void func_00000994(void *, void *, u32, s32) asm("$Lfunc_00000994");
extern void func_000009C0(s32, void *, s32, s32, u32, s32, s32) asm("$Lfunc_000009C0");

void StCdInterrupt(void) {
    volatile u16 st[3];
    u8 buf[4];
    u8 result[2];
    u16 *p;
    u32 mode;
    u32 i;
    s32 ret;
    u16 frame;

    if (StFinalSector == 1) {
        return;
    }
    if ((StRgb24 != 0) && ((*LD_00000BA8 & 0x01000000) != 0)) {
        StCdIntrFlag = 1;
        if (StEmu_Addr != 0) {
            StEmu_Idx += 1;
        }
        debug_cause = 1;
        return;
    }
    ret = CdReady(1, result);
    if (ret == 5) {
        return;
    }
    st[1] = result[0];
    st[2] = result[1];
    if (st[1] & 4) {
        debug_cause = 3;
        return;
    }
    p = (u16 *)((u8 *)StRingAddr + (StRingIdx1 << 5));
    B_00000BD8 = p;
    if (*p != 0) {
        if (StEmu_Addr != 0) {
            StEmu_Idx += 1;
        }
        debug_cause = 4;
        return;
    }
    *LD_00000B88 = 0;
    *LD_00000B94 = 0;
    *LD_00000B88 = 0;
    *LD_00000B94 = 0x80;
    *LD_00000B98 = 0x20943;
    *LD_00000B9C = 0x1323;
    if (StMode == 0) {
        for (i = 0; i < 4; i++) {
            buf[i] = *LD_00000B90;
        }
        for (i = 0; i < 8; i++) {
            (void)*LD_00000B90;
        }
    }
    mode = 0x11000000;
    if (StEmu_Addr != 0) {
        func_00000994(B_00000BD8, StEmu_Addr + (StEmu_Idx << 11), 8, 0);
    } else {
        func_000009C0(3, B_00000BD8, 0, 8, mode, 0, 0);
    }
    while (*LD_00000BB8 & 0x01000000) {
    }
    *(Word4 *)((u8 *)B_00000BD8 + 0x1C) = *(Word4 *)buf;
    *LD_00000B98 = 0x20843;
    *LD_00000B9C = 0x1325;
    if ((StSTART_FLAG == 1) && (StStartFrame != 0)) {
        if (StStartFrame != B_00000BD8[4]) {
            B_00000BD8[0] = 0;
            if (StEmu_Addr != 0) {
                StEmu_Idx += 1;
            }
            return;
        }
        StSTART_FLAG = 0;
    }
    if ((B_00000BD8[0] != 0x160) || (((B_00000BD8[1] >> 10) & 0x1F) != CChannel)) {
        if (StEmu_Addr != 0) {
            StEmu_Idx = 0;
        } else {
            (void)B_00000BD8[0];
        }
        debug_cause = 5;
        B_00000BD8[0] = 0;
        return;
    }
    if ((Stsector_offset != B_00000BD8[2]) ||
        ((Stframe_no != 0) && ((u32)Stframe_no != (u32)B_00000BD8[4]))) {
        Stframe_no = 0;
        Stsector_offset = 0;
        init_ring_status(StRingIdx2, StRingIdx1 - StRingIdx2);
        StRingIdx1 = StRingIdx2;
        B_00000BD8[0] = 0;
        if (StEmu_Addr != 0) {
            StEmu_Idx += 1;
        }
        debug_cause = 6;
        return;
    }
    if (B_00000BD8[2] == 0) {
        frame = B_00000BD8[4];
        Stsector_offset = 0;
        Stframe_no = frame;
        if ((StEndFrame != 0) && ((u32)frame >= (u32)StEndFrame)) {
            Stframe_no = 0;
            Stsector_offset = 0;
            init_ring_status(StRingIdx2, StRingIdx1 - StRingIdx2);
            StRingIdx1 = StRingIdx2;
            B_00000BD8[0] = 0;
            StSTART_FLAG = 1;
            if (StFunc2 != 0) {
                StFunc2();
            }
            if (StEmu_Addr != 0) {
                StEmu_Idx += 1;
            }
            debug_cause = 7;
            return;
        }
        if (((u32)(StRingSize - StRingIdx1) - 1) < B_00000BD8[3]) {
            if (StEndFrame == 0) {
                B_00000BD8[0] = 1;
                StSTART_FLAG = 1;
                if (StFunc2 != 0) {
                    StFunc2();
                }
                if (StEmu_Addr != 0) {
                    StEmu_Idx += 1;
                }
                debug_cause = 8;
                return;
            }
            if (*(s16 *)StRingAddr != 0) {
                B_00000BD8[0] = 0;
                if (StEmu_Addr != 0) {
                    StEmu_Idx += 1;
                }
                debug_cause = 9;
                return;
            }
            B_00000BD8[0] = 1;
            StRingIdx1 = 0;
            for (i = 0; i < 8; i++) {
                ((u32 *)StRingAddr)[i] = ((u32 *)B_00000BD8)[i];
            }
            B_00000BD8 = StRingAddr;
        }
        StRingIdx2 = StRingIdx1;
    }
    debug_cause = 0xA;
    Stsector_offset = Stsector_offset + 1;
    StRingBase = (u32 *)((u8 *)StRingAddr + (StRingSize << 5) + StRingIdx1 * 0x7E0);
    mode = 0x11000000;
    if (StRgb24 != 0) {
        *LD_00000B98 = 0x20943;
        *LD_00000B9C = 0x1323;
    } else {
        *LD_00000B98 = 0x21020843;
        mode = 0x11400100;
    }
    if ((B_00000BD8[3] - 1) == B_00000BD8[2]) {
        StFinalSector = 1;
        if (StEmu_Addr != 0) {
            func_00000994(StRingBase, StEmu_Addr + (StEmu_Idx << 11) + 0x20, 0x1F8, 1);
            StEmu_Idx += 1;
        } else {
            func_000009C0(3, StRingBase, 0, 0x1F8, mode, 1, 0);
        }
        Stsector_offset = 0;
        Stframe_no = 0;
        CChannel = StCHANNEL;
    } else if (StEmu_Addr != 0) {
        func_00000994(StRingBase, StEmu_Addr + (StEmu_Idx << 11) + 0x20, 0x1F8, 0);
        StEmu_Idx += 1;
    } else {
        func_000009C0(3, StRingBase, 0, 0x1F8, mode, 0, 0);
    }
    *LD_00000B9C = 0x1325;
    B_00000BD8[0] = 3;
    StRingIdx1 += 1;
    if ((StEmu_Addr != 0) && (StFinalSector != 0)) {
        data_ready_callback();
    }
}
