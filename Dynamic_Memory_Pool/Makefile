# EXEC of executable
EXEC = main

# Compiler to use
CC ?= gcc

# Compiler flags and options
CFLAGS_common = -Wall -std=gnu99
CFLAGS_DEBUG = -g
CFLAGS_opt  = -O0

# Source files
SRCS = main.c
SRCS_LIB = mem_pool.c generic.c

.PHONY: all
all: $(EXEC)

# Run the program
$(EXEC): $(SRCS_LIB)
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) $(CFLAGS_DEBUG) \
	$(SRCS_LIB) $@.c -o $@
	./main

# Use valgrind to detect error and memory leakage.
.PHONY: check
check: $(EXEC)
	valgrind --leak-check=yes -v ./main
# Clean
.PHONY: clean
clean:
	$(RM) $(EXEC) *.o
