# Tracing Shared Library

## Introduction
The practice of tracing shared library.

## How to build
```shell=
$ sh compiler.sh
```

## The anatomy of the executable
```shell=
$ objdump -xds ./main | less
```
  * Use objdump to list the related critical symbols, as follows:
    * start address 0x08048450
    * 080483e0 l    d  .init  00000000              .init
    * 08048410 l    d  .plt   00000000              .plt
    * 08048440 l    d  .plt.got       00000000              .plt.got
    * 08049f04 l    d  .dynamic       00000000              .dynamic
    * 08049ffc l    d  .got   00000000              .got
    * 0804a000 l    d  .got.plt       00000000              .got.plt
    * 0804a000 l     O .got.plt       00000000              _GLOBAL_OFFSET_TABLE_



## Start to trace the detail of the shared library

### _start
  * We can set a berakpoint at _start to observe the entire procedure from the entry point.
  * Use GDB with TUI (Text User Interface) to trace the program. Execute the following commands.
```shell=
$ gdb ./main
```
  * Use GDBTUI, press: "ctrl-x with 2" twice and input "start" to start.
  * Set the breakpoint at _start
```shell=
(gdb) b *_start
```


## Reference
 - [X86 Assembly/X86 Architecture](https://en.wikibooks.org/wiki/X86_Assembly/X86_Architecture)
 - [GOT and PLT for pwning.](https://systemoverlord.com/2017/03/19/got-and-plt-for-pwning.html)
 - [Shared Library 中 PLT 和 GOT 的使用機制](http://brandon-hy-lin.blogspot.tw/2015/12/shared-library-plt-got.html)
 - [Reverse debugging for gdb](http://hungmingwu-blog.logdown.com/posts/160187-reverse-debugging-for-gdb)
