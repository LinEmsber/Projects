# Tracing Shared Library

## Introduction
The practice of tracing shared library.

## How to build
```shell=
$ sh compiler.sh
```

## The anatomy of the executable
  * Use objdump to list the related critical symbols and functions, as follows:
```shell=
$ objdump -xds ./main | less
start address 0x08048450
...
080483e0 l    d  .init  00000000              .init
08048410 l    d  .plt   00000000              .plt
08048440 l    d  .plt.got       00000000              .plt.got
08049f04 l    d  .dynamic       00000000              .dynamic
08049ffc l    d  .got   00000000              .got
0804a000 l    d  .got.plt       00000000              .got.plt
0804a000 l     O .got.plt       00000000              _GLOBAL_OFFSET_TABLE_
...
    Contents of section .got.plt:
     804a000 049f0408 00000000 00000000 26840408
     804a010 36840408                           
...
08048410 <lib_a_func_two@plt-0x10>:
 8048410:       ff 35 04 a0 04 08       pushl  0x804a004
 8048416:       ff 25 08 a0 04 08       jmp    *0x804a008
 804841c:       00 00                   add    %al,(%eax)
...
08048420 <lib_a_func_two@plt>:
 8048420:       ff 25 0c a0 04 08       jmp    *0x804a00c
 8048426:       68 00 00 00 00          push   $0x0
 804842b:       e9 e0 ff ff ff          jmp    8048410 <_init+0x30>
...
08048430 <__libc_start_main@plt>:
 8048430:       ff 25 10 a0 04 08       jmp    *0x804a010
 8048436:       68 08 00 00 00          push   $0x8
 804843b:       e9 d0 ff ff ff          jmp    8048410 <_init+0x30>
...
08048450 <_start>:
 8048450:       31 ed                   xor    %ebp,%ebp
 8048452:       5e                      pop    %esi
 8048453:       89 e1                   mov    %esp,%ecx
 8048455:       83 e4 f0                and    $0xfffffff0,%esp
 8048458:       50                      push   %eax
 8048459:       54                      push   %esp
 804845a:       52                      push   %edx
 804845b:       68 e0 85 04 08          push   $0x80485e0
 8048460:       68 80 85 04 08          push   $0x8048580
 8048465:       51                      push   %ecx
 8048466:       56                      push   %esi
 8048467:       68 4b 85 04 08          push   $0x804854b
 804846c:       e8 bf ff ff ff          call   8048430 <__libc_start_main@plt>
 8048471:       f4                      hlt    
 8048472:       66 90                   xchg   %ax,%ax
 8048474:       66 90                   xchg   %ax,%ax
 8048476:       66 90                   xchg   %ax,%ax
 8048478:       66 90                   xchg   %ax,%ax
 804847a:       66 90                   xchg   %ax,%ax
 804847c:       66 90                   xchg   %ax,%ax
 804847e:       66 90                   xchg   %ax,%ax
```
  * Print shared object dependencies
```shell=
$ ldd ./main
        linux-gate.so.1 =>  (0xf7754000)
        ./lib_a.o (0xf774d000)
        ./lib_b.o (0xf774a000)
        libc.so.6 => /lib/i386-linux-gnu/libc.so.6 (0xf7575000)
        /lib/ld-linux.so.2 (0xf7755000)
```
  * Use objdump to dump the assembly of dynamic linker/loader, ld-linux.so.2
```shell=
$ objdump -xd /lib/ld-linux.so.2 | less

15000:       50                      push   %eax
15001:       51                      push   %ecx
15002:       52                      push   %edx
15003:       8b 54 24 10             mov    0x10(%esp),%edx
15007:       8b 44 24 0c             mov    0xc(%esp),%eax
1500b:       e8 d0 97 ff ff          call   e7e0 <_dl_rtld_di_serinfo@@GLIBC_PRIVATE+0x5bc0>
```

## Start to trace the detail of the shared library

### _start
  * We can set a berakpoint at _start to observe the entire procedure from the entry point.
  * Use GDB with TUI (Text User Interface) to trace the program. Execute the following commands.
```shell=
$ gdb ./main
```
  * Use GDBTUI, press: "ctrl-x with 2" twice and input "start" to start.
  * Set the breakpoint at _start and start the program
```shell=
(gdb) b *_start
(gdb) start
```
  * We can dump the content of .got.plt section. We can observe that the content of 0x804a004 and 0x804a008 are modified.
```
(gdb) x/5wx 0x804a000
0x804a000:      0x08049f04      0xf7ffd918      0xf7fee000      0x08048426
0x804a010:      0x08048436
```
  * Since we set the breakpoint at *_start, the program counter is hold at the entry point of the program.
  * Use the instruction step to execute the program
```
(gdb) si
```
  * When the program counter at 0x804846c, it call the function at 0x08048430, __libc_start_main@plt()
  * Back trace the entire stack and examine the value of the target addresses. It actually just jump to the next instruction.
```
(gdb) bt
#0  0x08048430 in __libc_start_main@plt ()
#1  0x08048471 in _start ()
(gdb) x/x *0x804a010
0x8048436 <__libc_start_main@plt+6>:    0x00000868
```
  * After that, the program counter jump to 0x8048410. It is actually the address of lib_a_func_two@plt()-0x10
  * The next instruction (0x8048416) is jump to the value of the address 0x804a008.
```
0x8048410                               pushl  0x804a004
0x8048416                               jmp    *0x804a008
```
```
(gdb) x/x *0x804a008
0xf7fee000:     0x8b525150
```
  * And then the program counter jump into the function of the dynamic linker/loader, /lib/ld-linux.so.2
```
(gdb) x $pc
0xf7fee000:     0x8b525150
(gdb) bt
#0  0xf7fee000 in ?? () from /lib/ld-linux.so.2
#1  0x08048471 in _start ()
```
  * We can examine the assembly of those address.
```
(gdb) x/x *0xf7fee003
0x1024548b:     Cannot access memory at address 0x1024548b
(gdb) x/x *0xf7fee007
0xc24448b:      Cannot access memory at address 0xc24448b
```
  *  We try to disassemble to obtain the address of the content.
```
0x1024548b -> 8b 54 24 10
0xc24448b  -> 8b 44 24 0c
```
  * Use grep to confirm it. There is only one result. Thus the content of 0xf7fee000 is from the address 0x15000 of /lib/ld-linux.so.2
```
$ objdump -xd /lib/ld-linux.so.2 | grep -B 1 "8b 44 24 0c" | grep "8b 54 24 10"
15003:	8b 54 24 10          	mov    0x10(%esp),%edx
```
```
15000:       50                      push   %eax
15001:       51                      push   %ecx
15002:       52                      push   %edx
15003:       8b 54 24 10             mov    0x10(%esp),%edx
15007:       8b 44 24 0c             mov    0xc(%esp),%eax
1500b:       e8 d0 97 ff ff          call   e7e0 <_dl_rtld_di_serinfo@@GLIBC_PRIVATE+0x5bc0>
```
  * Meanwhile, we also can calculate the offset of the address of dynamic linker/loader.
    * Use ldd to examine the shared object dependencies, /lib/ld-linux.so.2 (0xf7755000)
    * The program counter is at 0x15000 of /lib/ld-linux.so.2
    * The .text section of /lib/ld-linux.so.2 is start at 0x860
```
(gdb) p/x (0xf7fee000 - 0x15000) - 0xf7755000
$9 = 0x884000
```


## Reference
 - [X86 Assembly/X86 Architecture](https://en.wikibooks.org/wiki/X86_Assembly/X86_Architecture)
 - [GOT and PLT for pwning.](https://systemoverlord.com/2017/03/19/got-and-plt-for-pwning.html)
 - [Shared Library 中 PLT 和 GOT 的使用機制](http://brandon-hy-lin.blogspot.tw/2015/12/shared-library-plt-got.html)
 - [Reverse debugging for gdb](http://hungmingwu-blog.logdown.com/posts/160187-reverse-debugging-for-gdb)
 - [How process know address of shared library?](https://unix.stackexchange.com/questions/238930/how-process-know-address-of-shared-library)
 - [dynamic linker/loader](http://man7.org/linux/man-pages/man8/ld.so.8.html)
