#include "common.h"

extern u8 *D_00000190;

char *strtok(char *string, const char *delimiters) {
    u8 *s;
    const u8 *delimiter;
    u8 *token;
    s8 character;
    u8 delimiter_character;
    int is_delimiter;

    s = (u8 *)string;
    if (s == 0) {
        s = D_00000190;
        if (s == 0) {
            return 0;
        }
    }
    for (;;) {
        if ((character = *s++) == 0) {
            break;
        }
        is_delimiter = 0;
        for (delimiter = (const u8 *)delimiters; *(s8 *)delimiter != 0; delimiter++) {
            delimiter_character = *delimiter;
            if ((s8)delimiter_character == (s8)character) {
                is_delimiter = 1;
                break;
            }
        }
        if (!is_delimiter) {
            break;
        }
    }
    token = s - 1;
    if (character == 0) {
        D_00000190 = 0;
        return 0;
    }
    goto scan;

terminate_token:
    s[-1] = 0;
    D_00000190 = s;
    return (char *)token;

scan:
    while ((character = *s++) != 0) {
        for (delimiter = (const u8 *)delimiters; *(s8 *)delimiter != 0; delimiter++) {
            delimiter_character = *delimiter;
            if ((s8)delimiter_character == character) {
                goto terminate_token;
            }
        }
    }
    D_00000190 = 0;
    return (char *)token;
}
