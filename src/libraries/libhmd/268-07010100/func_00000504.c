/* len_param from the retained 07010100.C. */
static long func_00000504(long number)
{
    long i;

    for (i = 0; number > 0; i++)
        number >>= 1;
    return i;
}
