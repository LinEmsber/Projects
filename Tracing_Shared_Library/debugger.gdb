# The GDB script for tracing shared library
# How to use:
# $ gdb ./main -x ./debugger.gdb

# Windows layout
layout asm
layout reg
focus cmd

# Set breakpoints
break *_start
break *main

# Start the program
start

# The return point of the linker
break *0xf7fee01b

# The jump point before main function
