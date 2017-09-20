# Branch Preditcion

## Introduction

We compare three different kinds of array summations under a same condition.

## How to run

### Run program:
optimization for compilation time (default)
> gcc -O0 -Wall -g  main.c sum.c generic.c && ./a.out

optimization more for code size and execution time
> gcc -O2 -Wall -g  main.c sum.c generic.c && ./a.out

### Output the assembly code:

Use GCC:
> gcc -O2 -c sum.c
> gcc -O0 -c sum.c

Use perf:
> gcc -O2 -Wall -g main.c sum.c generic.c && sudo perf record ./a.out
> sudo perf report

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

## Function in assembly with -O0

### sum_array_normal():

```c
if (array[i] >= 128){
        sum += array[i];
}
```

```assembly
1.49  │1c:   mov    -0x8(%rbp),%eax
0.52  │      lea    0x0(,%rax,4),%rdx
0.03  │      mov    -0x18(%rbp),%rax
5.27  │      add    %rdx,%rax
27.24 │      mov    (%rax),%eax
2.55  │      cmp    $0x7f,%eax
3.07  │    ↓ jle    4c
17.08 │      mov    -0x8(%rbp),%eax
1.44  │      lea    0x0(,%rax,4),%rdx
0.22  │      mov    -0x18(%rbp),%rax
2.87  │      add    %rdx,%rax
4.69  │      mov    (%rax),%eax
6.22  │      add    %eax,-0x4(%rbp)

```

### sum_array_bitwise():

```c
sum += ~(array[i] - 128) >> 31 & array[i];
```

```assembly
0.02  │1c:   mov    -0x8(%rbp),%eax                                  
      │      lea    0x0(,%rax,4),%rdx                                
      │      mov    -0x18(%rbp),%rax                                 
11.85 │      add    %rdx,%rax                                        
8.88  │      mov    (%rax),%eax                                      
5.28  │      add    $0xffffff80,%eax                                 
6.64  │      not    %eax                                             
12.22 │      cltd                                                    
0.02  │      mov    -0x8(%rbp),%eax                                  
      │      lea    0x0(,%rax,4),%rcx                                
      │      mov    -0x18(%rbp),%rax                                 
12.60 │      add    %rcx,%rax                                        
0.10  │      mov    (%rax),%eax                                      
0.25  │      and    %edx,%eax                                        
30.31 │      add    %eax,-0x4(%rbp)                                  
```

### sum_array_cmov():

```c
sum += (array[i] >= 128) ? array[i] : 0;
```

```assembly
1.95  │1c:   mov    -0x8(%rbp),%eax                                
0.23  │      lea    0x0(,%rax,4),%rdx                              
0.02  │      mov    -0x18(%rbp),%rax                               
4.19  │      add    %rdx,%rax                                      
26.64 │      mov    (%rax),%eax                                    
2.06  │      cmp    $0x7f,%eax                                     
3.27  │    ↓ jle    4b                                             
14.50 │      mov    -0x8(%rbp),%eax                                
1.89  │      lea    0x0(,%rax,4),%rdx                              
0.02  │      mov    -0x18(%rbp),%rax                               
2.07  │      add    %rdx,%rax                                      
3.93  │      mov    (%rax),%eax                                    
0.80  │    ↓ jmp    50                                             
11.30 │4b:   mov    $0x0,%eax                                      
13.15 │50:   add    %eax,-0x4(%rbp)                                
```

## Function in assembly with -O2

### sum_array_normal():

```c
if (array[i] >= 128){
        sum += array[i];
}
```

```assembly
      │      xor    %r8d,%r8d
      │      xchg   %ax,%ax
10.11 │10:   mov    (%rdi,%rdx,4),%edx
9.01  │      cmp    $0x7f,%edx
25.27 │      cmovle %r8d,%edx
13.35 │      add    %edx,%eax
```

### sum_array_bitwise():

```c
sum += ~(array[i] - 128) >> 31 & array[i];
```

```assembly
1.42  │10:   mov    (%rdi,%rdx,4),%ecx
16.55 │      lea    -0x80(%rcx),%edx
0.49  │      not    %edx
22.02 │      sar    $0x1f,%edx
3.76  │      and    %ecx,%edx
20.95 │      add    %edx,%eax
```

### sum_array_cmov():

```c
sum += (array[i] >= 128) ? array[i] : 0;
```

```assembly
33.57 │10:   mov    (%rdi,%rcx,4),%ecx                   
      │      lea    (%rax,%rcx,1),%r8d                   
      │      add    $0xffffff80,%ecx                     
      │      lea    0x1(%rdx),%ecx                       
66.34 │      cmovge %r8d,%eax                            
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
