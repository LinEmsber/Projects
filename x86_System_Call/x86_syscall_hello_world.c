/* x86 system call hello world */

#include <stdio.h>

/* string for print_no_argu() */
char * string_no_argu = "print_no_argu(): x86 Hello World\n";

/* string for print_with_argu() */
char * string_with_argu = "print_with_argu(): x86 Hello World\n";

void print_no_argu()
{
	__asm__ volatile (
			"movl $33, %%edx \n\t"
			"movl %0, %%ecx  \n\t"
			"movl $0, %%ebx  \n\t"
			"movl $4, %%eax  \n\t"
			"int $0x80       \n\t"
			:
			: "r" (string_no_argu)
			: "edx", "ecx", "ebx");
}

void print_with_argu(int fd, void *buf, int count)
{
	/* call software interrupt 0x80 to invocate system call.
	 * pass system call number in eax ("a")
	 * pass fd in ebx ("b")
	 * pass buf in ecx ("c")
	 * pass count in edx ("d")
	 */
	__asm__ volatile (
			"int $0x80       \n\t"
			: "+b" (fd), "+c" (buf), "+d" (count)
			: "a" (4)
			: );
}

void my_exit()
{
	__asm__ volatile (
			"movl $42, %ebx \n\t"
			"movl $1, %eax  \n\t"
			"int $0x80      \n\t");
}

int main()
{
	print_no_argu();
	print_with_argu(1, string_with_argu, 35);
	my_exit();
}
