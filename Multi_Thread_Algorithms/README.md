# Mutual Exclusion Analysis


## Introduction

We want to compare and analysis many kinds of mutual exclusion algorithm.

## Peterson's algorithm

```bash
bool flag[0] = {false};
bool flag[1] = {false};
int turn;
```

```bash
P0:      flag[0] = true;
P0_gate: turn = 1;
         while (flag[1] == true && turn == 1)
         {
             // busy wait
         }
         // critical section
         ...
         // end of critical section
         flag[0] = false;
```

```bash
P1:      flag[1] = true;
P1_gate: turn = 0;
         while (flag[0] == true && turn == 0)
         {
             // busy wait
         }
         // critical section
         ...
         // end of critical section
         flag[1] = false;
```


## Dekker's algorithm

```bash
variables
        wants_to_enter : array of 2 booleans
        turn : integer

    wants_to_enter[0] ← false
    wants_to_enter[1] ← false
    turn ← 0   // or 1
```

```bash
p0:
   wants_to_enter[0] ← true
   while wants_to_enter[1] {
      if turn ≠ 0 {
         wants_to_enter[0] ← false
         while turn ≠ 0 {
           // busy wait
         }
         wants_to_enter[0] ← true
      }
   }

   // critical section
   ...
   turn ← 1
   wants_to_enter[0] ← false
   // remainder section
```

```bash
p1:
   wants_to_enter[1] ← true
   while wants_to_enter[0] {
      if turn ≠ 1 {
         wants_to_enter[1] ← false
         while turn ≠ 1 {
           // busy wait
         }
         wants_to_enter[1] ← true
      }
   }

   // critical section
   ...
   turn ← 0
   wants_to_enter[1] ← false
   // remainder section
```

## Result

```bash
========== gcc -O0 ==========
Peterson's algorithm
	excepted global value: 1000000000	calculated global value: 1000000000	time difference in sencond: 3.219449
Dekker's algorithm
	excepted global value: 1000000000	calculated global value: 1000000000	time difference in sencond: 3.465392
pthread_mutex_lock
	excepted global value: 1000000000	calculated global value: 1000000000	time difference in sencond: 2.147035

========== clang -O0 ==========
Peterson's algorithm
	excepted global value: 1000000000	calculated global value: 1000000000	time difference in sencond: 3.921504
Dekker's algorithm
	excepted global value: 1000000000	calculated global value: 1000000000	time difference in sencond: 3.932991
pthread_mutex_lock
	excepted global value: 1000000000	calculated global value: 1000000000	time difference in sencond: 1.983111

========== gcc -Ofast ==========
Peterson's algorithm
	excepted global value: 1000000000	calculated global value: 1000000000	time difference in sencond: 0.000037
Dekker's algorithm
	excepted global value: 1000000000	calculated global value: 1000000000	time difference in sencond: 0.002600
pthread_mutex_lock
	excepted global value: 1000000000	calculated global value: 1000000000	time difference in sencond: 0.000065

========== clang -Ofast ==========
Peterson's algorithm
	excepted global value: 1000000000	calculated global value: 1000000000	time difference in sencond: 0.000808
Dekker's algorithm
	excepted global value: 1000000000	calculated global value: 1000000000	time difference in sencond: 0.000046
pthread_mutex_lock
	excepted global value: 1000000000	calculated global value: 1000000000	time difference in sencond: 0.001016

```


## Reference:
 - [Peterson's algorithm Wiki](https://en.wikipedia.org/wiki/Peterson%27s_algorithm)
 - [Dekker's algorithm](https://en.wikipedia.org/wiki/Dekker%27s_algorithm)
 - [contrasting peterson's and dekker's algorithms](https://cs.stackexchange.com/questions/12621/contrasting-peterson-s-and-dekker-s-algorithms)
 - [Memory ordering](https://en.wikipedia.org/wiki/Memory_ordering)
 - [h15/examples](https://github.com/h15/examples)
