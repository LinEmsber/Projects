static int a;
extern int b;
extern void lib_b_func_one();

void lib_a_func_one()
{
	a = 0x55;
	b = 0x66;
}

void lib_a_func_two()
{
	lib_a_func_one();
	lib_b_func_one();
}
