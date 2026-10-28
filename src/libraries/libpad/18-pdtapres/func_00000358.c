#include "common.h"
#include "libpad-internal.h"

int func_00000358(PadInfo2 *info, int port) {
    PadInfo2 *rec;
    int i;
    int command;

    i = info->pad44[1] - 3;
    if (port) {
        rec = info->child + i / 8;
        port = i % 8 - 2;
    } else {
        rec = info;
        port = i;
    }
    command = rec->requestCommand;
    if (port >= 0) {
        switch (command) {
        case 0:
            if (port < 6 && rec->pad54[3 + port] == 0) {
                return 0;
            }
            return port < rec->actSize ? rec->actTable[port] : 0;
        case 0x4D:
            return port < rec->pad35[1] ? (*(u8 **)&rec->pad2C)[port] : 0xFF;
        default:
            return port < rec->pad35[1] ? (*(u8 **)&rec->pad2C)[port] : 0;
        }
    } else {
        rec = (PadInfo2 *)(port + 2);
        if (rec != 0) {
            return 0;
        }
        return (u8)(command != 0 ? command : 0x42);
    }
}
