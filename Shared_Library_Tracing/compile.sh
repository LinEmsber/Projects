# /bin/bash

# For arm Architecture
# CROSS_COMPILE=arm-linux-gnueabi-

# For x86 Architecture
CROSS_COMPILE=

# Build the shared libraries and the main executable
${CROSS_COMPILE}gcc -m32 -g3 -shared -fPIC lib_a.c -o lib_a.o
${CROSS_COMPILE}gcc -m32 -g3 -shared -fPIC lib_b.c -o lib_b.o
${CROSS_COMPILE}gcc -m32 -g3 main.c ./lib_a.o ./lib_b.o -o main
