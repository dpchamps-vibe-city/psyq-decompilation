extern void func_000002E4(unsigned int, unsigned int);
extern void *func_0000031C(unsigned int);
extern void func_000002C8(unsigned int);
extern void func_00000300(unsigned int);
extern void func_000002AC(unsigned int);
extern void func_00000290(void);
extern void *func_0000036C(unsigned int, unsigned int, unsigned int);

s32 SetConf(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_s0_2;
    s32 temp_s0;
    s32 eight;
    s32 tgt2;
    s32 var_s0;
    s32 var_v0;
    s32 n;
    unsigned char *temp_a0;
    unsigned char *temp_a0_2;
    unsigned char *temp_a0_3;
    unsigned char *temp_v0;
    unsigned char *temp_v0_2;
    unsigned char *temp_v0_3;
    unsigned char *var_v1;
    unsigned char *var_v1_2;
    unsigned char *var_v1_3;
    unsigned char *var_v1_4;

    var_s0 = 0;
    func_000002E4(0xA000E800, 0x1000);
    n = 0x20;
    temp_v0 = (unsigned char *)func_0000031C(0x20);
    if (temp_v0 != 0) {
        var_v1 = temp_v0;
        var_v0 = n;
        do {
            *var_v1 = 0;
            var_v0 -= 1;
            var_v1 += 1;
        } while (var_v0 > 0);
        D_000003A0->unk0 = (unsigned int)temp_v0;
        D_000003A0->unk4 = n;
        var_s0 = n;
    }
    if (var_s0 != 0) {
        func_000002C8(0);
        func_00000300(3);
        var_s0_2 = arg0 * 0x1C;
        var_v1_2 = (unsigned char *)func_0000031C(var_s0_2);
        if (var_v1_2 == 0) {
            var_s0_2 = 0;
        } else {
            temp_a0 = var_v1_2 + var_s0_2;
            D_000003A0->unk24 = var_s0_2;
            D_000003A0->unk20 = (unsigned int)var_v1_2;
            if (var_v1_2 < temp_a0) {
                do {
                    *(unsigned int *)(var_v1_2 + 4) = 0;
                    var_v1_2 += 0x1C;
                } while (var_v1_2 < temp_a0);
            }
        }
        if (var_s0_2 != 0) {
            temp_s0 = arg1 * 0xC0;
            eight = 8;
            D_000003A0->unkC = eight;
            D_000003A0->unk14 = temp_s0;
            tgt2 = arg1;
            temp_v0_2 = (unsigned char *)func_0000031C(eight);
            if ((temp_v0_2 == 0) || (temp_v0_3 = (unsigned char *)func_0000031C(temp_s0), (temp_v0_3 == 0))) {
                var_s0_2 = 0;
            } else {
                Obj *pd;
                temp_a0_2 = temp_v0_2 + 8;
                var_v1_3 = temp_v0_2;
                if (temp_v0_2 < temp_a0_2) {
                    do {
                        *(unsigned int *)var_v1_3 = 0;
                        var_v1_3 += 8;
                    } while (var_v1_3 < temp_a0_2);
                }
                temp_a0_3 = temp_v0_3 + (tgt2 * 0xC0);
                var_v1_4 = temp_v0_3;
                if (temp_v0_3 < temp_a0_3) {
                    do {
                        *(unsigned int *)var_v1_4 = 0x1000;
                        var_v1_4 += 0xC0;
                    } while (var_v1_4 < temp_a0_3);
                }
                pd = D_000003A0;
                var_s0_2 = eight + temp_s0;
                *(unsigned int *)temp_v0_3 = 0x4000;
                *(unsigned int *)temp_v0_2 = (unsigned int)temp_v0_3;
                pd->unk8 = (unsigned int)temp_v0_2;
                pd->unk10 = (unsigned int)temp_v0_3;
            }
            if (var_s0_2 != 0) {
                func_000002AC(1);
                func_00000290();
                func_0000036C(arg0, arg1, arg2);
                return 1;
            }
            return 0;
        }
        return 0;
    }
    return 0;
}
