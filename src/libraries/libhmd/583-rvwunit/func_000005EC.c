static int func_000005EC(int x) {
    int n = 0;

    while (x > 0) {
        x >>= 1;
        n++;
    }
    return n;
}
