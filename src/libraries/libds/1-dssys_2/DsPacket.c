#include "common.h"

struct DslLOC;
typedef struct DslLOC DslLOC;
typedef void (*DslCB)(u8, u8 *);

extern int _DsPacket2(u8 mode, DslLOC *pos, u8 com, DslCB func, int count, int flag);

int DsPacket(u8 mode, DslLOC *pos, u8 com, DslCB func, int count) {
    return _DsPacket2(mode, pos, com, func, count, 1);
}
