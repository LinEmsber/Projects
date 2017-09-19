# EXEC of executable
EXEC = main

# Compiler to use
CC ?= gcc

# Compiler flags and options
CFLAGS_common = -Wall -std=gnu99
CFLAGS_opt  = -O0
CFLAGS_debug = -g -D__DEBUG

# Source files
SRCS = main.c
SRCS_LIB = sum_array.c generic.c

.PHONY: all
all: $(EXEC)

# Run the compilation program.
$(EXEC): $(SRCS_LIB)
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) $(SRCS_LIB) $@.c -o $@
	./main

# Test the algorithem.
.PHONY: test
test: $(SRCS_LIB)
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) $(CFLAGS_debug) $(SRCS_LIB) main.c -o main
	./main

# Use valgrind to detect error and memory leakage.
.PHONY: check
check: $(EXEC)
	valgrind --leak-check=yes -v ./main

# Clean
.PHONY: clean
clean:
	$(RM) $(EXEC) *.o
