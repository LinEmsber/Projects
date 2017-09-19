# Mutual Exclusion Analysis


## Introduction

We want to compare and analysis many kinds of mutual exclusion algorithm.

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
 - [contrasting peterson's and dekker's algorithms](https://cs.stackexchange.com/questions/12621/contrasting-peterson-s-and-dekker-s-algorithms)
 - [Memory ordering](https://en.wikipedia.org/wiki/Memory_ordering)
 - [h15/examples](https://github.com/h15/examples)
