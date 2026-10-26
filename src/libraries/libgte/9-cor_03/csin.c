int csin(int a)
{
    if (a < 0) {
        a = -a;
        a %= 4096;
        return -csin_1(a);
    }
    a %= 4096;
    return csin_1(a);
}
