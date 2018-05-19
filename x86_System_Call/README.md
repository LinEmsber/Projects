# x86 system call

## Introduction

This is a simple demonstration of the invocation of the system call directly.
We write a print function which will invocate *write* system call directly.
It needs to know the ABI of x86 and the interface of Linux system call *write*


## X86 Assembly/Interfacing with Linux
Syscalls are the interface between user programs and the Linux kernel. They are used to let the kernel perform various system tasks, such as file access, process management and networking. In the C programming language, you would normally call a wrapper function which executes all required steps or even use high-level features such as the standard IO library.

On Linux, there are several ways to make a syscall. This page will focus on making syscalls by calling a software interrupt using int *$0x80* or *syscall*. This is an easy and intuitive method of making syscalls in assembly-only programs.

## Making a syscall
For making a syscall using an interrupt, you have to pass all required information to the kernel by copying them into general purpose registers.

Each syscall has a fixed number. You specify the syscall by writing the number into the eax/rax register.

On both Linux x86 and Linux x86_64 systems you can make a syscall by calling interrupt 0x80 using the int $0x80 command.

| Syscall # | Param 1 | Param 2 | Param 3 | Param 4 | Param 5 | Param 6 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| eax | ebx | ecx | edx | esi | edi | ebp |

| Return value |
| ------------ |
| eax          |


## Source Code
```c
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
```

## Build & Execution

### Compile the object file
```bash
gcc -static -m32 -fno-builtin -c x86_syscall_hello_world.c
```

### Link the objudct file
```bash
ld -m elf_i386 -static -lc --entry main x86_syscall_hello_world.o -o x86_syscall_hello_world
```

### Use objdump to examine
```bash
objdump -xds ./a.out | less
```

### Fast build and execute
```bash
gcc -static -m32 -fno-builtin -c x86_syscall_hello_world.c && ld -m elf_i386 -static -lc --entry main x86_syscall_hello_world.o -o x86_syscall_hello_world
```


## References
 - [靜態連結](https://hackmd.io/s/Bypzjl0LG)
 - [x86 assembly Interfacting with Linux](https://en.wikibooks.org/wiki/X86_Assembly/Interfacing_with_Linux)
 - [Writing Functions with Inline Assembly](https://msdn.microsoft.com/en-us/library/5sds75we.aspx)
 - [Inline assembler](https://en.wikipedia.org/wiki/Inline_assembler)
 - [GCC-Inline-Assembly-HOWTO](https://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html)
