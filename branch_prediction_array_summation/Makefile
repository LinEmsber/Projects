# EXEC of executable
EXEC = main

# compiler to use
CC ?= gcc

# compiler flags and options
CFLAGS_common = -Wall -std=gnu99
CFLAGS_opt  = -O0
CFLAGS_debug = -g -D__DEBUG

# source files
SRCS = main.c
SRCS_LIB = sum_array.c generic.c

.PHONY: all
all: $(EXEC)

# test the algorithem
test: $(SRCS_LIB)
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) $(CFLAGS_debug) $(SRCS_LIB) main.c -o main

# run the compilation
$(EXEC): $(SRCS_LIB)
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) $(SRCS_LIB) $@.c -o $@

# using valgrind to test execute, main.
.PHONY: run
run: $(EXEC)
	valgrind --leak-check=yes -v ./main

# clean
.PHONY: clean
clean:
	$(RM) $(EXEC) *.o
