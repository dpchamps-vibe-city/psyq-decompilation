#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include "library/libgte-log.h"

int cln(int a) {
    int i;
    int n;
    int m[7];
    int b[7];
    int ans;

    n = 0x14 - Lzc(a);
    if (n >= 0)
        a >>= n;
    else
        a <<= -n;
    m[0] = a;
    b[0] = 0;
    for (i = 1; i < 7; i++) {
        int v = m[i - 1];
        int y = v + (v >> i);
        if (y >= 0x1000) {
            m[i] = v;
            b[i] = b[i - 1];
        } else {
            m[i] = y;
            b[i] = b[i - 1] - H_ln_tbl[i];
        }
    }
    ans = b[6] - 0x1000;
    ans += m[6];
    return ans + n * H_ln_tbl[0];
}
