#include "common.h"
#include <sys/types.h>
#include <libgte.h>

extern EVECTOR *CLIPEvbf;
extern s32 CLIPFarz;
extern s32 CLIPHdkx;
extern s32 CLIPHdky;
extern s32 CLIPKdhx;
extern s32 CLIPKdhy;
extern s32 CLIPNearz;

void InitClip(EVECTOR *evbfad, long hw, long vw, long h, long near, long far) {
    s32 temp_a1;
    s32 temp_v0;
    s32 temp_v1;

    temp_v1 = (s32) (((u32) hw >> 0x1F) + hw) >> 1;
    temp_a1 = h << 0xC;
    temp_v0 = (s32) (((u32) vw >> 0x1F) + vw) >> 1;
    CLIPEvbf = evbfad;
    CLIPNearz = near;
    CLIPFarz = far;
    CLIPHdkx = temp_a1 / temp_v1;
    CLIPHdky = temp_a1 / temp_v0;
    CLIPKdhx = (s32) (temp_v1 << 0xC) / h;
    CLIPKdhy = (s32) (temp_v0 << 0xC) / h;
}
