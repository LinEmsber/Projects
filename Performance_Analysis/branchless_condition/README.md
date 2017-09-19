# Branch Preditcion

## Introduction

We compare three different kinds of array summations under a same condition.

## How to run

### Run program:
optimization for compilation time (default)
> gcc -O0 -Wall -g  main.c sum.c generic.c && ./a.out

optimization more for code size and execution time
> gcc -O2 -Wall -g  main.c sum.c generic.c && ./a.out

### output the assembly code:
> gcc -O2 -c sum.c

> gcc -O0 -c sum.c

## Function source code in C

sum_array_normal():
```c
int sum_array_normal(int * array, size_t size)
{
        unsigned int i;
        int sum = 0;
        for (i = 0; i < size; i++){
                if (array[i] >= 128){
                        sum += array[i];
                }
        }
        return sum;
}
```

sum_array_bitwise():
```c
int sum_array_bitwise(int * array, size_t size)
{
        unsigned int i;
        int sum = 0;
        for (i = 0; i < size; i++){
                sum += ~(array[i] - 128) >> 31 & array[i];
        }
        return sum;
}
```

sum_array_cmov():
```c
int sum_array_cmov(int * array, size_t size)
{
        unsigned int i;
        int sum = 0;
        for (i = 0; i < size; i++){
                sum += (array[i] >= 128) ? array[i] : 0;
        }
        return sum;
}
```

## Function in assembly

sum_array_normal():
```assembly
.L4:
	movl	-8(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$127, %eax
	jle	.L3
	movl	-8(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	addl	%eax, -4(%rbp)
.L3:
	addl	$1, -8(%rbp)
.L2:
	movl	-8(%rbp), %eax
	cmpq	-32(%rbp), %rax
	jb	.L4
```

sum_array_bitwise():

```assembly
.L8:
	movl	-8(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	addl	$-128, %eax
	notl	%eax
	cltd
	movl	-8(%rbp), %eax
	leaq	0(,%rax,4), %rcx
	movq	-24(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	andl	%edx, %eax
	addl	%eax, -4(%rbp)
	addl	$1, -8(%rbp)

```

sum_array_cmov():

```assembly
.L14:
	movl	-8(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$127, %eax
	jle	.L12
	movl	-8(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	jmp	.L13
.L12:
	movl	$0, %eax
.L13:
	addl	%eax, -4(%rbp)
	addl	$1, -8(%rbp)
.L11:
	movl	-8(%rbp), %eax
	cmpq	-32(%rbp), %rax
	jb	.L14
```
## Result

optimization for compilation time (default)
```bash
NORMAL
	time difference in second: 2.096273
	sum: 31212356000
BITWISE
	time difference in second: 0.746373
	sum: 31212356000
CMOV
	time difference in second: 2.203104
	sum: 31212356000
NORMAL with sorting
	time difference in second: 0.643599
	sum: 31212356000
BITWISE with sorting
	time difference in second: 0.748326
	sum: 31212356000
CMOV with sorting
	time difference in second: 0.758482
	sum: 31212356000

```

optimization more for code size and execution time

```bash
gcc -O2 -Wall -g  main.c sum.c generic.c && ./a.out
NORMAL
	time difference in second: 0.273749
	sum: 31135405000
BITWISE
	time difference in second: 0.255345
	sum: 31135405000
CMOV
	time difference in second: 0.224535
	sum: 31135405000
NORMAL with sorting
	time difference in second: 0.282016
	sum: 31135405000
BITWISE with sorting
	time difference in second: 0.250761
	sum: 31135405000
CMOV with sorting
	time difference in second: 0.225506
	sum: 31135405000
```

## References

 - [Why is it faster to process a sorted array than an unsorted array?](http://stackoverflow.com/questions/11227809/why-is-it-faster-to-process-a-sorted-array_original-than-an-unsorted-array_original)
 - [Performance analysis in Linux](https://www.collabora.com/news-and-blog/blog/2017/03/21/performance-analysis-in-linux/)
 - [gcc -o / -O option flags](http://www.rapidtables.com/code/linux/gcc/gcc-o.htm)
