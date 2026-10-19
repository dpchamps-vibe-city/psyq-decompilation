#include "common.h"
#include <sys/types.h>
#include <stdio.h>
#include <libcd.h>

typedef union {
    int addr;
    CdlLOC i;
} LBA;

typedef struct {
    int num;
    int parentNum;
    LBA lba;
    char name[0x20];
} CdlDIR;

extern s32 cached_dir_num_ __asm__("$LD_00000BD8");
extern CdlFILE file_[] __asm__("$LB_00000BE8");
extern CdlDIR dire_[] __asm__("$LB_000011E8");
extern u8 load_buf_[0x800] __asm__("$LB_000027E8");
extern char str_dir_not_found[] __asm__("$LRO_STR_00000B54");
extern char str_searching[] __asm__("$LRO_STR_00000B74");
extern short str_dot[] __asm__("$LRO_STR_00000B90");
extern short str_dotdot[] __asm__("$LRO_STR_00000B94");
extern char str_entry[] __asm__("$LRO_STR_00000B98");
extern char str_count[] __asm__("$LRO_STR_00000BB4");

extern void *memcpy(void *dest, const void *src, u32 n);

static s32 func_00000974(s32, s32, u8 *) __asm__("$Lfunc_00000974");

static s32 func_000006D8(s32 arg0) __asm__("$Lfunc_000006D8");

static s32 func_000006D8(s32 arg0) {
    LBA entryLba;
    u8 *entry;
    s32 i;
    short *namePtr;

    if (arg0 == cached_dir_num_) {
        return 1;
    }

    if (func_00000974(1, (dire_ - 1)[arg0].lba.addr, load_buf_) != 1) {
        if (CD_debug > 0) {
            printf(str_dir_not_found);
        }
        return -1;
    }
    if (CD_debug > 1) {
        printf(str_searching);
    }
    entry = load_buf_;
    i = 0;
    while (entry < load_buf_ + sizeof(load_buf_)) {
        if (entry[0] == 0) {
            break;
        }
        entryLba.i = ((LBA *)&entry[2])->i;
        CdIntToPos(entryLba.addr, &file_[i].pos);
        ((LBA *)&file_[i].size)->i = ((LBA *)&entry[0xA])->i;
        switch (i) {
        case 0:
            namePtr = (short *)file_[i].name;
            __builtin_memcpy(namePtr, str_dot, 2);
            break;
        case 1:
            namePtr = (short *)file_[i].name;
            __builtin_memcpy(namePtr, str_dotdot, 3);
            break;
        default:
            ((void *(*)(void *, const void *, u32))memcpy)(file_[i].name, &entry[0x21], entry[0x20]);
            file_[i].name[entry[0x20]] = '\0';
            break;
        }
        if (CD_debug > 1) {
            printf(str_entry, file_[i].pos.minute,
                   file_[i].pos.second, file_[i].pos.sector, file_[i].size,
                   file_[i].name);
        }
        entry += entry[0];
        if (++i >= CdlMAXFILE) {
            break;
        }
    }
    cached_dir_num_ = arg0;
    if (i < CdlMAXFILE) {
        file_[i].name[0] = '\0';
    }
    if (CD_debug > 1) {
        printf(str_count, i);
    }
    return 1;
}
