#!/bin/bash

gcc -O0 -D_S if_switch.c && perf stat --repeat 100 ./a.out
gcc -O0 -D_I if_switch.c && perf stat --repeat 100 ./a.out

gcc -O2 -D_S if_switch.c && perf stat --repeat 100 ./a.out
gcc -O2 -D_I if_switch.c && perf stat --repeat 100 ./a.out
