# Array Summation

Using Gprof or perf to conduct an analysis of array summation.
We use different summation algorithms to compare the resources use.

-------------------------------------------------------------------------------
## Usage and explanation:
-------------------------------------------------------------------------------

### Gprof:

1. compile it, remember to add option "-pg" for gporf, and "-O0" for default optimization for
compilation time.
> gcc -O0 -Wall -pg sum_array_01.c

2. After we compile the output file, we MUST to run this program once to create a file, gmont.out,
for analysis.
> ./a.out

3. run Gprof to analyze the result.
> gprof -b ./a.out gmon.out

or
> gcc -O0 -Wall -pg sum_array_01.c && ./a.out && gprof -b ./a.out gmon.out


### Perf:

compile it
> gcc -O0 -Wall -g sum_array_01.c

1. find which function have the most branch-misses?
perf with option "-e" to specify the events: branch-misses, branch-instructions

> gcc -O0 -Wall -pg sum_array_01.c && sudo perf record -e branch-misses:u,branch-instructions:u ./a.out && sudo perf report

2. find the most overhead functions
add doller sign behind executiable binary, and perf with option "-p" to specify PID.
$! is the PID of the most recent background command.

> gcc -O0 -Wall -pg sum_array_01.c && ./a.out & sudo perf top -p $!

## TODO:
use faster method (better algorithms) to do array summing.
add time diff
multi-thread


## References:
http://os.51cto.com/art/200703/41426.htm
https://www.ptt.cc/bbs/C_and_CPP/M.1246071002.A.A54.html
https://en.wikipedia.org/wiki/Duff's_device
http://www.rapidtables.com/code/linux/gcc/gcc-o.htm
https://embedded2016.hackpad.com/ep/pad/static/YkqjhwgnQcA
