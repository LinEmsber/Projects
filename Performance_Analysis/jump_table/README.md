# Jump table

## Introduction
Compare switch and if-else in different compiler optimization.

## Result

|                   | -O0, switch case | -O0, if-else case | -O2, switch case | -O2, if-else case |
| :-------------    | :-------------- | :------------ |:------------- |:-------------- |
| task-clock (msec) | 1404           | 2707           | 853           | 1351           |
| context-switches  | 17             | 101            | 16            | 48             |
| instructions      | 13,402,214,190 | 19,904,667,350 | 9,876,556,824 | 16,877,669,641 |
| branches          | 1,975,392,420  | 6,225,824,315  | 1,925,279,224 | 6,150,475,779  |
| branch-misses     | 41,199         | 98,597         | 59,044        | 22,391         |

```bash
> gcc -O0 -D_S if_switch.c && perf stat ./a.out

Performance counter stats for './a.out' (100 runs):

      1404.886591      task-clock (msec)         #    0.999 CPUs utilized            ( +-  0.04% )
               17      context-switches          #    0.012 K/sec                    ( +- 72.51% )
                0      cpu-migrations            #    0.000 K/sec                    ( +-100.00% )
               43      page-faults               #    0.031 K/sec                    ( +-  0.54% )
    4,927,368,298      cycles                    #    3.507 GHz                      ( +-  0.01% )
  <not supported>      stalled-cycles-frontend  
  <not supported>      stalled-cycles-backend   
   13,402,214,190      instructions              #    2.72  insns per cycle          ( +-  0.00% )
    1,975,392,420      branches                  # 1406.087 M/sec                    ( +-  0.00% )
           41,199      branch-misses             #    0.00% of all branches          ( +-  2.04% )

      1.406180719 seconds time elapsed                                          ( +-  0.04% )
```

```bash
> gcc -O0 -D_I if_switch.c && perf stat ./a.out

Performance counter stats for './a.out' (100 runs):

      2707.232120      task-clock (msec)         #    0.998 CPUs utilized            ( +-  0.05% )
              101      context-switches          #    0.037 K/sec                    ( +- 51.78% )
                0      cpu-migrations            #    0.000 K/sec                    ( +- 50.92% )
               43      page-faults               #    0.016 K/sec                    ( +-  0.54% )
    9,494,848,416      cycles                    #    3.507 GHz                      ( +-  0.03% )
  <not supported>      stalled-cycles-frontend  
  <not supported>      stalled-cycles-backend   
   19,904,667,350      instructions              #    2.10  insns per cycle          ( +-  0.00% )
    6,225,824,315      branches                  # 2299.701 M/sec                    ( +-  0.00% )
           98,597      branch-misses             #    0.00% of all branches          ( +- 60.33% )

      2.711619355 seconds time elapsed                                          ( +-  0.08% )
```

```bash
> gcc -O2 -D_S if_switch.c && perf stat ./a.out

Performance counter stats for './a.out' (100 runs):

       853.264158      task-clock (msec)         #    0.998 CPUs utilized            ( +-  0.05% )
               16      context-switches          #    0.019 K/sec                    ( +- 79.17% )
                0      cpu-migrations            #    0.000 K/sec                  
               43      page-faults               #    0.050 K/sec                    ( +-  0.35% )
    2,988,252,528      cycles                    #    3.502 GHz                      ( +-  0.02% )
  <not supported>      stalled-cycles-frontend  
  <not supported>      stalled-cycles-backend   
    9,876,556,824      instructions              #    3.31  insns per cycle          ( +-  0.00% )
    1,925,279,224      branches                  # 2256.370 M/sec                    ( +-  0.00% )
           59,044      branch-misses             #    0.00% of all branches          ( +-  1.81% )

      0.854555334 seconds time elapsed                                          ( +-  0.08% )
```

```bash
> gcc -O2 -D_I if_switch.c && perf stat ./a.out

Performance counter stats for './a.out' (100 runs):

      1351.773295      task-clock (msec)         #    0.999 CPUs utilized            ( +-  0.14% )
               48      context-switches          #    0.036 K/sec                    ( +- 53.48% )
                0      cpu-migrations            #    0.000 K/sec                    ( +- 50.92% )
               43      page-faults               #    0.032 K/sec                    ( +-  0.46% )
    4,738,802,976      cycles                    #    3.506 GHz                      ( +-  0.03% )
  <not supported>      stalled-cycles-frontend  
  <not supported>      stalled-cycles-backend   
   16,877,669,641      instructions              #    3.56  insns per cycle          ( +-  0.00% )
    6,150,475,779      branches                  # 4549.931 M/sec                    ( +-  0.00% )
           22,391      branch-misses             #    0.00% of all branches          ( +-  6.72% )

      1.353729506 seconds time elapsed                                          ( +-  0.13% )
```



## Reference
 - [c switch and jump tables](https://stackoverflow.com/questions/17061967/c-switch-and-jump-tables)
 - [What is a jump table?](https://stackoverflow.com/questions/48017/what-is-a-jump-table)
 - [jump table examples in C](https://stackoverflow.com/questions/9932212/jump-table-examples-in-c)
 - [Branch table](https://en.wikipedia.org/wiki/Branch_table)
