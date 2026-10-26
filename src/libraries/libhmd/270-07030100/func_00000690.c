static long func_00000690(long number)
{
	long i;

	for (i = 0; number > 0; i++)
		number >>= 1;

	return i;
}
