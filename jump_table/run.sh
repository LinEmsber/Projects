#!/bin/bash

gcc -O0 -D_S if_switch.c && perf stat ./a.out
gcc -O0 -D_I if_switch.c && perf stat ./a.out

gcc -O3 -D_S if_switch.c && perf stat ./a.out
gcc -O3 -D_I if_switch.c && perf stat ./a.out
