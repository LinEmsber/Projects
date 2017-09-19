# Array Summation

Using Gprof or perf to conduct an analysis of array summation.
We use different summation algorithms to compare the resources use.

## Usage and explanation:
 1. Run the compilation program.
> make
 2. Test the algorithem.
> make test
 3. Use valgrind to detect error and memory leakage.
> make check

### Gprof:

 - compile it, remember to add option "-pg" for gporf, and "-O0" for default optimization for
compilation time.

```bash
> gcc -O0 -Wall -pg main.c sum_array.c generic.c
```

 - After we compile the output file, we MUST to run this program once to create a file, gmont.out,
for analysis.

```bash
> ./a.out
```
 - run Gprof to analyze the result.

```bash
> gprof -b ./a.out gmon.out

or
> gcc -O0 -Wall -pg main.c sum_array.c generic.c && ./a.out && gprof -b ./a.out gmon.out
```

### Perf:

 - compile it

```bash
> gcc -O0 -Wall -g main.c sum_array.c generic.c
```

 - find which function have the most branch-misses?
perf with option "-e" to specify the events: branch-misses, branch-instructions

```bash
> gcc -O0 -Wall -pg main.c sum_array.c generic.c && sudo perf record -e branch-misses:u,branch-instructions:u ./a.out && sudo perf report
```

 - find the most overhead functions
add doller sign behind executiable binary, and perf with option "-p" to specify PID.
$! is the PID of the most recent background command.

```bash
> gcc -O0 -Wall -pg main.c sum_array.c generic.c && ./a.out & sudo perf top -p $!
```

## Result

We run the program, and the result as follows:

```bash
Simplest summation, time difference in sencond: 3.420176
Loop unrolling, time difference in sencond: 3.059372
Duff's device, time difference in sencond: 3.093178
```

## TODO:
 - use faster method (better algorithms) to do array summing.
 - add time diff
 - multi-thread


## References:
 - [Loop unrolling, Duff's device](https://www.ptt.cc/bbs/C_and_CPP/M.1246071002.A.A54.html)
 - [Duff's_device wiki](https://en.wikipedia.org/wiki/Duff's_device)
 - [gcc -o / -O option flags](http://www.rapidtables.com/code/linux/gcc/gcc-o.htm)
 - [NCKU embedded2016 HW1](https://embedded2016.hackpad.com/ep/pad/static/YkqjhwgnQcA)
